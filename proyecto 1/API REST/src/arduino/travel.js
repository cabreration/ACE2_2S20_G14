let common = require('./common')

module.exports = (app, aws_utils) => {

    // traveling route
    app.get('/traveling', async(req, res) => {
        let location = req.query.ubicacion
        let state = req.query.estado
        let angle = req.query.angulo
        let distance = req.query.distancia

        if (state == 3) {
            common.obstacles += 1
        }

        // post to Dynamo
        let ddb = aws_utils.ddb
        let record_id = Date.now()

        // string location
        let string_location = ''
        switch (location) {
            case "0":
                string_location = 'en punto de partida'
                break
            case "1":
                string_location = 'en recorrido'
                break
            case "2":
                string_location = 'en punto de entrega'
        }

        // string state
        let string_state = ''
        switch (state) {
            case "0":
                string_state = 'en reposo'
                break
            case "1":
                string_state = 'en camino a entrega'
                break
            case "2":
                string_state = 'en camino a buzon'
                break
            case "3":
                string_state = 'detenido por un obstaculo'
                break
        }

        ddb.putItem({
            TableName: 'Automail_Travel',
            Item: {
                "record_id": { S: record_id.toString() },
                "location": { S: string_location },
                "state": { S: string_state },
                "angle": { S: angle.toString() },
                "distance": { S: distance.toString() }
            }
        }, (err, data) => {
            if (err) {
                console.log(err)
            }
        })

        res.send(common.state)
    })
}