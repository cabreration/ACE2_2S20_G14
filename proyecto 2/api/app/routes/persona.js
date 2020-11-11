module.exports = app => {
    const persona = require("../controllers/persona");

    var router = require("express").Router();

    // Agrega un usuario
    router.post("/UserInfo", persona.UserInfo);

    // Agrega un usuario con temperatura a la base de datos
    router.get("/val", persona.UserTemperatura);

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