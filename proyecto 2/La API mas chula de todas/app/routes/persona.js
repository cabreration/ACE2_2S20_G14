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

    // La ruta de la api de productos sera url/productos
    app.use("/", router);
};