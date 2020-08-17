let Common = require('./static_values')

const webpush = require('../mobile/notifier')
const options = {
    priority: "normal",
    timeToLive: 60 * 60 * 24
}

module.exports = (app, admin) => {

    app.get('/arduino', async(req, res) => {
        Common.WEIGHT = req.query.peso
        Common.SANITIZER = req.query.spray
        let flag = Common.EXISTS 
        Common.EXISTS = req.query.objeto == 1 ? true : false
    
        if (!flag && Common.EXISTS) {
            const payload = {
                notification: {
                    title: 'Entrega',
                    body: 'Hay un objeto nuevo en el buzon'
                }
            }
        
            try {
                await admin.messaging().sendToDevice(Common.PUSH, payload, options)
            }
            catch (e) {
                console.error(e);
            }
            
            //await webpush.sendNotification(Common.PUSH, payload)
        }

        if (Common.SANITIZER < 10) {
            const payload = JSON.stringify({
                title: 'Liquido Bajo',
                message: 'Necesitas rellenar el liquido de Sanitizacion'
            })
        
            //await webpush.sendNotification(Common.PUSH, payload)
        }

        res.send(`Los datos en memoria son: peso = ${Common.WEIGHT}, liquido = ${Common.SANITIZER}, objeto = ${Common.EXISTS}`)
    })

}