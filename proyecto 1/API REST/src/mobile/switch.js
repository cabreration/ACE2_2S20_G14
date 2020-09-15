let common = require('../arduino/common')

module.exports = (app) => {
    app.post('/switch', (req, res) => {
        let state = req.body.Estado
        if (state == 0) {
            common.state = 'inactivo'
        }
        else {
            common.state = 'activo'
        }

        console.log(common.state);
        res.send('copy that')
    })
}