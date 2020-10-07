module.exports = app => {
    const producto = require("../controllers/entrega");

    var router = require("express").Router();

    // Obtener datos para el reporte 1
    router.get("/reporte1", producto.findR1);

    // Obtener datos para el reporte 2
    router.get("/reporte2", producto.findR2);

    // Obtener datos para el reporte 2
    router.get("/reporte3", producto.findR3);
    
    // Obtener datos para el reporte 2
    router.get("/reporte4", producto.findR4);
    
    // Obtener datos para el reporte 2
    router.get("/reporte5", producto.findR5);
    
    // La ruta de la api de entrega
    app.use("/entrega", router);
};