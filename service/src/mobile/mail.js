let Common = require('../arduino/static_values')

module.exports = (app) => {

    app.get('/mail', async(req, res) => {
        console.log(`peso: ${Common.WEIGHT}, spray: ${Common.SANITIZER}`)
        res.send({ peso: Common.WEIGHT, liquido: Common.SANITIZER })
    })

}