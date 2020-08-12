const { Router } = require('express')
const router = Router()

const webpush = require('../mobile/notifier')
let pushSubscription;

let Common = require('../arduino/static_values')

router.post('/subscription', async (req, res) => {
    pushSubscription = req.body;
    Common.PUSH = req.body;
    res.status(200).json();

    const payload = JSON.stringify({
        title: 'Notificacion',
        message: 'las notificaciones funcionan'
    })

    try {
        await webpush.sendNotification(pushSubscription, payload)
    }
    catch (e) {
        console.log(e)
    }
})

module.exports = router