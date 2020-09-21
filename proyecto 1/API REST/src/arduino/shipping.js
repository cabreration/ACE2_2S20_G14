let common = require('./common')

module.exports = (app, aws_utils, firebase) => {

    // traveling route
    app.get('/shipping', async(req, res) => {
        let state = req.query.estado
        let weight = req.query.peso == undefined ? 0 : req.query.peso

        // post to Dynamo
        let ddb = aws_utils.ddb
        let record_id = Date.now()

        // string state
        let string_state = ''
        switch (state) {
            case "0":
                string_state = 'iniciando entrega'
                break
            case "1":
                string_state = 'entregando paquete'
                break
            case "2":
                string_state = 'regresando al buzon'
                break
        }

        // date
        let date = new Date()
        let hours = date.getHours().toString()
        let minutes = date.getMinutes().toString()

        // save general info
        ddb.putItem({
            TableName: 'Automail_Delivery',
            Item: {
                "record_id": { S: record_id.toString() },
                "state": { S: string_state },
                "weight": { S: weight.toString() },
                "obstacles": { S: common.obstacles.toString() },
                "time" : { S: `${hours}:${minutes}` }
            }
        }, (err, data) => {
            if (err) {
                console.log(err)
            }
        })

        // save travel time to database
        if (state == 1 || state == 2) {
            // get previous time
            let docClient = new aws_utils.AWS.DynamoDB.DocumentClient()
            let params = {
                TableName: 'Automail_Delivery'
            }

            docClient.scan(params, (err, data) => {
                if (err) console.log(err)
                else {
                    let data_array = data.Items
                    let previous_time = null
                    let rec_runner = 0
                    for (let i = 0; i < data_array.length; i++) {
                        let record = data_array[i]
                        if (state == 1) {
                            if (record.record_id > rec_runner 
                                && record.state == 'iniciando entrega') {
                                    previous_time = record.time 
                                    rec_runner = record.record_id
                            }
                        }
                        else {
                            if (record.record_id > rec_runner 
                                && record.state == 'entregando paquete') {
                                    previous_time = record.time
                                    rec_runner = record.record_id 
                            }
                        }
                    }

                    // compute time
                    let processed_time = previous_time.split(':')
                    let prev_hours = Number(processed_time[0])
                    let prev_mins = Number(processed_time[1])
                    let cur_hours = Number(hours)
                    let cur_mins = Number(minutes)
                    let trav_hours = 0
                    let trav_mins = 0
                    if (prev_hours > cur_hours) 
                        cur_hours = cur_hours + 24
                    
                    trav_hours = cur_hours - prev_hours

                    let flag = false
                    if (prev_mins > cur_mins) {
                        cur_mins = cur_mins + 60
                        flag = true
                    }
                    
                    trav_mins = cur_mins - prev_mins
                    trav_mins = trav_hours * 60 + trav_mins
                    
                    trav_mins = flag ? trav_mins - 60 : trav_mins

                    ddb.putItem({
                        TableName: 'Automail_TravelTimes',
                        Item: {
                            'att_id': { S: Date.now().toString() },
                            'time': { S: `${trav_mins}` },
                            'state': { S: state }
                        }
                    }, (err, data) => {
                        if (err) {
                            console.log(err)
                        }
                    })
                }
            })

        }

        // push notifications
        const options = {
            priority: "normal",
            timeToLive: 60 * 60 * 24
        };

        let payload = null

        if (state == 0) { 
            payload = {
                notification: {
                    title: "Inicio de Entrega",
                    body: `El dispositivo se dispone a salir del buzon,
                    con un peso de ${weight.toString()}`
                },
                data: {
                    msj: `El peso del objeto es de ${weight.toString()},
                        el dispositivo salio el ${(new Date()).toDateString()}`,
                    click_action: 'FLUTTER_NOTIFICATION_CLICK'
                }
            };
        }
        else if (state == 1) {
            payload = {
                notification: {
                    title: "Entrega de paquete",
                    body: `El dispositivo se encuentra completando la entrega,
                    con un peso de ${weight.toString()} y un total de ${common.obstacles}`
                },
                data: {
                    msj: `El peso del objeto es de ${weight},
                     el dispositivo salio el ${(new Date()).toDateString()}
                     y se encontraron ${common.obstacles} obstaculos`,
                    click_action: 'FLUTTER_NOTIFICATION_CLICK'
                }
            };
        }
        else {
            payload = {
                notification: {
                    title: "Retorno a buzon",
                    body: `El dispositivo se dispone a regresar al buzon con un total de ${common.obstacles} obstaculos`,
                },
                data: {
                    msj: `El dispositivo salio el ${(new Date()).toDateString()}
                     y se encontraron ${common.obstacles} obstaculos`,
                    click_action: 'FLUTTER_NOTIFICATION_CLICK'
                }
            };
        }

        (async () => {
            try{
             let result = await firebase.admin.messaging().sendToDevice(firebase.token, payload, options);
             console.log(result);
            }catch(err){
             console.log(err);
            }
        })();

        // restart the count of obstacles
        if (state != 0) {
            common.obstacles = 0
        }

        res.send(common.state);
    })
}