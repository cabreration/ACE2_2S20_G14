let Common = require('./static_values')

const webpush = require('../mobile/notifier')
const options = {
    priority: "normal",
    timeToLive: 60 * 60 * 24
}

module.exports = (app, admin) => {

    app.get('/arduino', async(req, res) => {
        Common.PREVIOUS = Common.WEIGHT
        Common.WEIGHT = req.query.peso
        Common.SANITIZER = req.query.spray
    
        // Si los pesos son diferentes y mayores a cero entonces se notifica de nuevo
        if (Common.WEIGHT > 0 && (Math.abs(Common.WEIGHT - Common.PREVIOUS) > 1)) {
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

        // Si el sanitizador esta en menos que 10% y no se ha enviado la notificacion
        if (Common.SANITIZER < 10 && !Common.SA_SENT) {
            const payload = JSON.stringify({
                title: 'Liquido Bajo',
                message: 'Necesitas rellenar el liquido de Sanitizacion'
            })
        
            //await webpush.sendNotification(Common.PUSH, payload)
        }

        res.send(`Los datos en memoria son: peso = ${Common.WEIGHT}, liquido = ${Common.SANITIZER}, objeto = ${Common.EXISTS}`)
    })

}