module.exports = app => {
    const persona = require("../controllers/persona");

    var router = require("express").Router();

    // Agrega un usuario
    router.post("/UserInfo", persona.UserInfo);

    // Agrega un usuario con temperatura a la base de datos
    router.get("/val", persona.UserTemperatura);

    router.get("/val2", (req, res) => {
        let temp = req.params.temp / 1000;
        let time = req.params.tiem / 1000;

        console.log(`Temperatura: ${temp} °C`);
        console.log(`Tiempo: ${time} segundos`)

        res.send("agregado");
    });

    // Agrega un usuario con temperatura a la base de datos
    router.get("/obtenerPersonas", persona.getAll);

    // Agrega un usuario con temperatura a la base de datos
    router.get("/empezo", persona.empezo);

    //SOLO PARA PRUEBAS, RETORNAR SI 1/10 de las veces que se pida.
    router.get("/empezo2", (req, res) =>{
        if (Math.floor(Math.random() * 10) % 10){
            return res.send("no");
        }

        return res.send("si");
    })

    // La ruta de la api de productos sera url/productos
    app.use("/", router);
};