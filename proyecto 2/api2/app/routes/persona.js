module.exports = app => {
    const persona = require("../controllers/persona");

    var router = require("express").Router();

    // Agrega un usuario
    router.post("/UserInfo", persona.UserInfo);

    // Agrega un usuario con temperatura a la base de datos
    router.get("/val", persona.UserTemperatura); // <-- DESCOMENTAR

    // Agrega un usuario con temperatura a la base de datos
    router.get("/obtenerPersonas", persona.getAll);

    // Agrega un usuario con temperatura a la base de datos
    router.get("/empezo", persona.empezo);  // <-- DESCOMENTAR

    // Devuelve el tiempo promedio
    router.get("/getTiempoPromedio", persona.getTiempoPromedio);
    
    // Devuelve el tiempo promedio
    router.get("/getTemperaturaPromedio", persona.getTemperaturaPromedio);
    
    // Devuelve concurrenca por hora
    router.get("/getConcurrenciaDias", persona.getConcurrenciaDias);

    // Devuelve promedio por hora
    router.get("/getPromedioHoras", persona.getPromedioHoras);
    
    app.use("/", router);
};