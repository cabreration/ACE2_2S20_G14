let common = require('./common')

module.exports = (app) => {
    app.get('/status', (req, res) => {
        let query = req.query.consulta

        if (query == 0) {
            res.send(common.state)
        }
        else if (query == 1) {
            // reset common
            common.state = 'inactivo'
            common.obstacles = 0
        }
    })
}