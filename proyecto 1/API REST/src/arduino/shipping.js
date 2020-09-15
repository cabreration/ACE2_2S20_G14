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

        // restart the count of obstacles
        if (state != 0) {
            common.obstacles = 0
        }

        res.send(common.state);
    })
}