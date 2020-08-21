let Common = require('../arduino/static_values')

module.exports = (app) => {

    app.get('/mail', async(req, res) => {
        res.send({ peso: Common.WEIGHT, liquido: Common.SANITIZER })
    })

}