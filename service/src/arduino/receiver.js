let Common = require('./static_values')

const options = {
    priority: "normal",
    timeToLive: 60 * 60 * 24
}

const token = 'djz0Li1hRJ-4E7RALt3q2w:APA91bF_m05oPFsEfJwHuJWsJ5UZFQuggcvOPouSoWtLc_SyQzRvTW3psC8yK5GtGvxeuO6t05pekAu5N2Mk2xfkrKYZiSQWBjfw_CJh0DFmk_fbHRyVbrPyriVLS3OyWeaWisiLq8Ha';

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
                },
                data: {
                    msj: 'notificacion1',
                    click_action: 'FLUTTER_NOTIFICATION_CLICK'
                }
            }
        
            try {
                await admin.messaging().sendToDevice(token, payload, options)
            }
            catch (e) {
                console.error(e);
            }
        }

        // Si el sanitizador esta en menos que 10% y no se ha enviado la notificacion
        if (Common.SANITIZER < 10 && Common.SANITIZER >= 1 && !Common.SA_SENT) {
            const payload = {
                notification: {
                    title: 'Liquido',
                    body: 'El liquido de Sanitizacion esta por agotarse'
                },
                data: {
                    msj: 'notificacion2',
                    click_action: 'FLUTTER_NOTIFICATION_CLICK'
                }
            }

            try {
                await admin.messaging().sendToDevice(token, payload, options)
                Common.SA_SENT = true
            }
            catch (e) {
                console.error(e);
            }
        }

        if (Common.SANITIZER < 1 && !Common.SA_SENT2) {
            const payload = {
                notification: {
                    title: 'Liquido',
                    body: 'El liquido de sanitizacion se ha agotado'
                },
                data: {
                    msj: 'notificacion3',
                    click_action: 'FLUTTER_NOTIFICATION_CLICK'
                }
            }

            try {
                await admin.messaging().sendToDevice(token, payload, options)
                Common.SA_SENT2 = true
            }
            catch (e) {
                console.error(e);
            }
        }

        if (Common.SANITIZER > 10) {
            Common.SA_SENT = false
            Common.SA_SENT2 = false
        }
            

        res.send(`Los datos en memoria son: peso = ${Common.WEIGHT}, liquido = ${Common.SANITIZER}`)
    })

}