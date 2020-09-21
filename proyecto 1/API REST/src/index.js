// API Dependencies
const express = require('express')
const cors = require('cors')
const bodyParser = require('body-parser')
const app = express()
const port = 3000
const morgan = require('morgan')
var AWS = require('aws-sdk')


// Firebase notifications dependencies
const admin = require('firebase-admin')
const serviceAccount = require('./credentials.json')
admin.initializeApp({
    credential: admin.credential.cert(serviceAccount),
    databaseURL: 'https://automailarqui.firebaseio.com'
})
const token = 'ccTZYNoCQISzt7j3ETfjYp:APA91bEZgzSF76B4JRRNBPHogKOo2np64qcQ_kB-3l4pzgsQymorhBJAxO3uV8C13Zw0HnMSPj4zYlqFv9cc4Ictjz9-YDJApUxZ9ZP7dGySNpgNIZBc5FBH2gLmv29-wFiT5fViJ_k6'
firebase = {
    admin: admin,
    token: token
}


// Web server configuration
app.use(cors())
app.use(morgan('dev'))
app.use(bodyParser.urlencoded({extended: false}))
app.use(bodyParser.json({limit: '50mb', extended: true}))
app.listen(port, () => {console.log('I love you ' + port)})


// AWS configuration
const aws_keys = {
    apiVersion: '2012-08-10',
    region: 'us-east-2',
    endpoint: 'http://dynamodb.us-east-2.amazonaws.com'
}
AWS.config.loadFromPath('./src/awsConfig.json')
const ddb = new AWS.DynamoDB(aws_keys)
aws_utils = {
    AWS: AWS,
    ddb: ddb
}


// Routes
const travel = require('./arduino/travel')(app, aws_utils)
const shipping = require('./arduino/shipping')(app, aws_utils, firebase)
const device_state = require('./arduino/status')(app)
const switchEngine = require('./mobile/switch')(app)
const reporterEngine = require('./mobile/reporter')(app, aws_utils)


// push notification test
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
        msj: 'notificacion de prueba',
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