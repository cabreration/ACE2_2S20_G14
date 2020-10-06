const express = require("express");
const bodyParser = require("body-parser");
const cors = require("cors");
const app = express();

const db = require('./app/models/index');

app.use(cors());

// Recibir datos de tipo JSON
app.use(bodyParser.json());

require("./app/routes/entrega")(app);

const dbConnect = (url) => {
    db.mongoose
        .connect(url)
        .catch(err => {
            console.error("** No se pudo conectar a la base de datos **");
            console.error(err);
            process.exit();
        });
};

const server = app.listen(process.env.PORT || 5000, () => {
    api.dbConnect(process.env.TESTING ? db.testUrl : db.url);
});

let api = { server: server, app: app, dbConnect: dbConnect };

module.exports = api;