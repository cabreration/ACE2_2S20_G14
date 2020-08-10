let Common = require('./static_values')

module.exports = (app) => {

    app.get('/arduino', async(req, res) => {
        Common.WEIGHT = req.query.peso
        Common.SANITIZER = req.query.spray
        let flag = Common.EXISTS 
        Common.EXISTS = req.query.objeto == 1 ? true : false
    
        if (!flag && Common.EXISTS) {
            // envio de notificacion a usuario 
        }

        res.send(`Los datos en memoria son: peso = ${Common.WEIGHT}, liquido = ${Common.SANITIZER}, objeto = ${Common.EXISTS}`)
    })

}