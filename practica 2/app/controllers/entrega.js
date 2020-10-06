const db = require("../models");
const Entregas = db.entregas;

exports.Entregas = Entregas;


// Devuelve el peso y la hora por dia
exports.findR1 = (req, res) => {
    if (!req.query.date) {
        return res.status(400).send({
            message: "Se necesira la fecha para obtener los datos"
        });
    }

    const date = req.query.date;

    Entregas.find({dia_entrega:date})
    .then(data => {
        if (data.length == 0) {
            return res.status(404).json({
                message: `La fecha ${date} no se encuentra`
            });
        }

        jsonArray = []

        data.forEach(item => {
            jsonArray.push({peso:item.peso_paquete,hora:item.hora_entrega})
        });

        const l = jsonArray.length;
        let j, temp;

        for ( let i = 1; i < l; i++ ) {
            j = i;
            temp = jsonArray[ i ];
            while ( j > 0 && jsonArray[ j - 1 ].hora > temp.hora ) {
                jsonArray[ j ] = jsonArray[ j - 1 ];
                j--;
            }
            jsonArray[ j ] = temp;
        }

        return res.json(jsonArray);
    })
    .catch(err => {
        return res.status(500).json({
            message: "Error al obtener los datos",
            db_message: err.message || ""
        });
    });;
};

// Devuelve cantidad de paquetes por dia en un mes
exports.findR2 = (req, res) => {
    if (!req.query.date) {
        return res.status(400).send({
            message: "Se necesira la fecha para obtener los datos"
        });
    }

    const date = new Date(req.query.date);

    Entregas.find()
    .then(data => {
        let jsonArray = []

        data.forEach(item => {
            let dateItem = new Date(item.dia_entrega)
            if(date.getMonth()==dateItem.getMonth()&&date.getFullYear()==dateItem.getFullYear()){
                jsonArray.push(item.dia_entrega.split('/')[1])
            }
        });

        let jsonArrayData = []
                
        for(let i=0;i<jsonArray.length;i++){
            let insert = true
            if(i==0){
                jsonArrayData.push({dia:jsonArray[0], paquetes:1})
                continue 
            }

            for(let j=0;j<jsonArrayData.length;j++){
                if(jsonArrayData[j].dia==jsonArray[i]){
                    jsonArrayData[j].paquetes += 1
                    insert = false
                    break
                }
            };

            if(insert){
                jsonArrayData.push({dia:jsonArray[i], paquetes:1})
            }
        }

        let arrayData = []
        
        for(let i=1;i<32;i++){
            for(let j=0;j<jsonArrayData.length;j++){
                if(i+''==parseInt(jsonArrayData[j].dia,10)){
                    arrayData.push({dia:i, paquetes:jsonArrayData[j].paquetes})
                    break;
                }
            }
        }

        return res.json(arrayData);
    })
    .catch(err => {
        return res.status(500).json({
            message: "Error al obtener los datos",
            db_message: err.message || ""
        });
    });;
};

// Devuelve cantidad de obstaculos por dia
exports.findR3 = (req, res) => {
    if (!req.query.date) {
        return res.status(400).send({
            message: "Se necesira la fecha para obtener los datos"
        });
    }

    const date = req.query.date;

    Entregas.find({dia_entrega:date})
    .then(data => {
        if (data.length == 0) {
            return res.status(404).json({
                message: `La fecha ${date} no se encuentra`
            });
        }

        jsonArray = []

        data.forEach(item => {
            jsonArray.push({hora:item.hora_entrega,obstaculos_ida:item.obstaculos_ida,obstaculos_regreso:item.obstaculos_regreso})
        });

        const l = jsonArray.length;
        let j, temp;

        for ( let i = 1; i < l; i++ ) {
            j = i;
            temp = jsonArray[ i ];
            while ( j > 0 && jsonArray[ j - 1 ].hora > temp.hora ) {
                jsonArray[ j ] = jsonArray[ j - 1 ];
                j--;
            }
            jsonArray[ j ] = temp;
        }

        return res.json(jsonArray);
    })
    .catch(err => {
        return res.status(500).json({
            message: "Error al obtener los datos",
            db_message: err.message || ""
        });
    });;
};

// Devuelve tiempo ida y regreso por dia
exports.findR4 = (req, res) => {
    if (!req.query.date) {
        return res.status(400).send({
            message: "Se necesira la fecha para obtener los datos"
        });
    }

    const date = req.query.date;

    Entregas.find({dia_entrega:date})
    .then(data => {
        if (data.length == 0) {
            return res.status(404).json({
                message: `La fecha ${date} no se encuentra`
            });
        }

        jsonArray = []

        data.forEach(item => {
            jsonArray.push({hora:item.hora_entrega,tiempo_ida:item.tiempo_ida,tiempo_regreso:item.tiempo_regreso})
        });

        const l = jsonArray.length;
        let j, temp;

        for ( let i = 1; i < l; i++ ) {
            j = i;
            temp = jsonArray[ i ];
            while ( j > 0 && jsonArray[ j - 1 ].hora > temp.hora ) {
                jsonArray[ j ] = jsonArray[ j - 1 ];
                j--;
            }
            jsonArray[ j ] = temp;
        }

        return res.json(jsonArray);
    })
    .catch(err => {
        return res.status(500).json({
            message: "Error al obtener los datos",
            db_message: err.message || ""
        });
    });;
};


// Devuelve promedio de tiempos por dia en un mes
exports.findR5 = (req, res) => {
    if (!req.query.date) {
        return res.status(400).send({
            message: "Se necesira la fecha para obtener los datos"
        });
    }

    const date = new Date(req.query.date);

    Entregas.find()
    .then(data => {
        let jsonArray = []

        data.forEach(item => {
            let dateItem = new Date(item.dia_entrega)
            if(date.getMonth()==dateItem.getMonth()&&date.getFullYear()==dateItem.getFullYear()){
                jsonArray.push({dia:parseInt(item.dia_entrega.split('/')[1],10),tiempo_ida:item.tiempo_ida,tiempo_regreso:item.tiempo_regreso})
            }
        });

        const l = jsonArray.length;
        let j, temp;

        for ( let i = 1; i < l; i++ ) {
            j = i;
            temp = jsonArray[ i ];
            while ( j > 0 && jsonArray[ j - 1 ].dia > temp.dia ) {
                jsonArray[ j ] = jsonArray[ j - 1 ];
                j--;
            }
            jsonArray[ j ] = temp;
        }

        let contador = 0
        let arrayData = []
        

        for ( let i = 0; i < jsonArray.length; i++ ) {
            let insertar = true;
            for ( let j = 0; j < arrayData.length; j++ ) {
                if(arrayData[j].dia == jsonArray[i].dia){
                    arrayData[j].tiempo_ida = (arrayData[j].tiempo_ida+jsonArray[i].tiempo_ida)/2
                    arrayData[j].tiempo_regreso = (arrayData[j].tiempo_regreso+jsonArray[i].tiempo_regreso)/2
                    insertar = false
                }   
            }
            if(insertar){
                arrayData.push(jsonArray[i])
            }
        }

        return res.json(arrayData);
    })
    .catch(err => {
        return res.status(500).json({
            message: "Error al obtener los datos",
            db_message: err.message || ""
        });
    });;
};