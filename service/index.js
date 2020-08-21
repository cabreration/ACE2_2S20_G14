const express = require('express')
const bodyParser = require('body-parser')
const cors = require('cors')
const app = express()
const port = 3000
const morgan = require('morgan')

// FCM
var admin = require('firebase-admin')
var serviceAccount = require('./credentials.json')
admin.initializeApp({
    credential: admin.credential.cert(serviceAccount),
    databaseURL: "https://automailarqui.firebaseio.com"
})

var token = 'djz0Li1hRJ-4E7RALt3q2w:APA91bF_m05oPFsEfJwHuJWsJ5UZFQuggcvOPouSoWtLc_SyQzRvTW3psC8yK5GtGvxeuO6t05pekAu5N2Mk2xfkrKYZiSQWBjfw_CJh0DFmk_fbHRyVbrPyriVLS3OyWeaWisiLq8Ha';

const options = {
    priority: "normal",
    timeToLive: 60 * 60 * 24
};

const payload = {
    notification: {
       title: "Servidor Encendido",
       body: "Test de notificacion",
    },
    data: {
        msj: 'notificacion1',
        click_action: 'FLUTTER_NOTIFICATION_CLICK'
    }
};

(async () => {
    try{
     let result = await admin.messaging().sendToDevice(token, payload, options);
     console.log(result);
    }catch(err){
     console.log(err);
    }
})();

// Everything to build the server
app.use(cors())
app.use(morgan('dev'))
app.use(express.urlencoded({extended: false}))
app.use(express.json())

app.listen(port, () => console.log(`listening on port ${port}`))

const arduino = require('./src/arduino/receiver')(app, admin)
const mail = require('./src/mobile/mail')(app)