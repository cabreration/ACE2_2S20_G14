const db = require("../models");
const AWS = require('aws-sdk');
var crypto = require('crypto');

var md5sum = crypto.createHash('md5');

const s3 = new AWS.S3({
    accessKeyId: "AKIAVBMZRCURELPTYIXJ",
    secretAccessKey: "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"
});

const myBucket = 'arturobucket';
//arq2p2
const Persona = db.persona;

var persona = {
    nombre: "Nombre Apellido",
    dpi: 1234567891234567,
    temperatura: 0,
    tiempo: 0,
    imagen: "1234",
    fecha: '',
    hora: ''
}

let personas = []

// Guardar informacion del usuario
exports.empezo = (req, res) => {
    if(personas.length != 0){
        return res.status(200).send("si");
    }else{
        return res.status(200).send("no");
    }
};

// Guardar informacion del usuario
exports.UserInfo = (req, res) => {
    if (!req.body.nombre || !req.body.dpi || !req.body.base64) {
        return res.status(400).json({ message: "Se enviaron datos incompletos." });
    }

    let imagen = req.body.dpi + req.body.base64.substring(30, 40)+".jpg";
    persona.dpi = req.body.dpi;
    persona.nombre = req.body.nombre;
    persona.imagen = "    https://arq2p2.s3.us-east-2.amazonaws.com/fotos/"+imagen

    var decodedImage;
    try{
        decodedImage = new Buffer(req.body.base64.replace('data:image/jpeg;base64,',''), 'base64');
    }catch(err){        
        return res.status(400).json({
            message: "No se agrego la imagen."
        });
    }

    let parametros = {
        Bucket: "arq2p2",
        Key: "fotos/" + imagen,
        Body: decodedImage
    }
    let f = new Date();
    let dia = f.getDate();
    let mes = f.getMonth() + 1;
    let ano = f.getFullYear();
    persona.fecha = `${dia}/${mes}/${ano}`;
    persona.hora = `${f.getHours()}:${f.getMinutes()}:${f.getSeconds()}`;
    personas.push(persona);

    s3.putObject(parametros, (err, data) => {
        if(err){
            return res.status(400).json({
                message: "Error al almacenar los datos."
            });
        }
        return res.status(200).json({
            message: "Datos almacenados, eperando temperatura."
        });
    });
};

exports.UserTemperatura = (req, res) => {
    if(personas.length == 0){
        return res.send("no hay personas");
    }
    let temp = personas.pop();
    if(temp.nombre == ""){
        return res.send("no hay nombre");
    }

    if (!req.query.temp || !req.query.tiem) {
        return res.send(!req.query.temp ? "no hay temperatura" : "no hay tiempo");
    }

    let tiempo;
    let temperatura;

    try {
        tiempo = parseInt(req.query.tiem)/1000;
        temperatura = parseInt(req.query.temp)/1000;
    } catch (error) {
        tiempo = 0;
        temperatura = 0;
    }
    
    temp.temperatura = temperatura;
    temp.tiempo = tiempo;

    Persona.create(temp, (err, persona) => {
            if (err) {
                console.log("****** ERROR EN LA BASE DE DATOS ******");
                console.log(err);
                console.log("***************************************");
                
                return res.send("error en la base de datos");
            }
            return res.send("agregado correctamente");
        });
};

// Obtener todas las personas
exports.getAll = (_req, res) => {
    Persona.find({})
        .then(data => {
            return res.json(data);
        })
        .catch(err => {
            return res.status(500).json({
                message: "Error al retornar a las personas en la BD",
                db_message: err.message || ""
            });
        });
};

// Obtiene el tiempo promedio
exports.getTiempoPromedio = (_req, res) => {
    Persona.find({})
        .then(data => {
            let total = 0;
            data.forEach(element => {
                total += element.tiempo
            });
            total = total / data.length

            return res.json({tiempoPromedio: total});
        })
        .catch(err => {
            return res.status(500).json({
                message: "Error al retornar a las personas en la BD",
                db_message: err.message || ""
            });
        });
};

// Obtiene el tiempo promedio
exports.getTemperaturaPromedio = (_req, res) => {
    Persona.find({})
        .then(data => {
            let total = 0;
            data.forEach(element => {
                total += element.temperatura
            });
            total = total / data.length

            return res.json({temperatura: total});
        })
        .catch(err => {
            return res.status(500).json({
                message: "Error al retornar a las personas en la BD",
                db_message: err.message || ""
            });
        });
};

// Horas de concurrencia
exports.getConcurrenciaDias = (_req, res) => {
    let dias = ["dom", "lun", "mar", "mie", "jue", "vie", "sab"];
    Persona.find({})
        .then(data => {
            let horas = new Map();

            for(let i=0;i<7;i++){
                horas.set(dias[i],0)
            }
            data.forEach(element => {
                let fecha = new Date(element.fecha)
                let dia = fecha.getUTCDay()
                    
                for(let i=0;i<7;i++){
                    if(dia == i){
                        horas.set(dias[i], horas.get(dias[i])+1);
                        break;
                    }
                }
            });
            let array = [];
            
            for(let i=0;i<7;i++){
                array.push({dia:dias[i], personas: (horas.get(dias[i])/data.length)*100})
            }

            return res.json({dias: array});
        })
        .catch(err => {
            return res.status(500).json({
                message: "Error al retornar a las personas en la BD",
                db_message: err.message || ""
            });
        });
};

// Horas de concurrencia
exports.getPromedioHoras= (_req, res) => {
    Persona.find({})
        .then(data => {
            let horas = new Map();

            for(let i=0;i<24;i++){
                horas.set(i+'',0)
            }
            data.forEach(element => {
                let hora = element.hora.split(':')[0];
                let cantidad = horas.get(hora)+1;
                horas.set(hora, cantidad);
            });
            let array = [];
            
            for(let i=0;i<24;i++){
                array.push({hora:i+'', personas: (horas.get(i+'')/data.length)*100})
            }

            return res.json({horas: array});
        })
        .catch(err => {
            return res.status(500).json({
                message: "Error al retornar a las personas en la BD",
                db_message: err.message || ""
            });
        });
};
