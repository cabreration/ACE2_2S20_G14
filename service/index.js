// Env vars
require('dotenv').config()

const express = require('express')
const bodyParser = require('body-parser')
const cors = require('cors')
const app = express()
const port = 80
const morgan = require('morgan')
const path = require('path')

// Everything to build the server
app.use(cors())
app.use(morgan('dev'))
app.use(express.urlencoded({extended: false}))
app.use(express.json())

// Routing
app.use(require('./src/routes/index'))

// Static Content
app.use(express.static(path.join(__dirname, 'src/public')))

app.listen(port, () => console.log(`listening on port ${port}`))

const arduino = require('./src/arduino/receiver')(app)
const mail = require('./src/mobile/mail')(app)