let common = require('../arduino/common')

module.exports = (app) => {
    app.post('/switch', (req, res) => {
        let state = req.body.Estado
<<<<<<< Updated upstream
        if (state == 'i') {
=======
        if (state == "i") {
>>>>>>> Stashed changes
            common.state = 'inactivo'
        }
        else {
            common.state = 'activo'
        }

        console.log(common.state);
        res.send('copy that')
    })
}