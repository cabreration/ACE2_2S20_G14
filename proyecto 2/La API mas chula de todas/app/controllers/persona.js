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
    imagen: ""
}

// Guardar informacion del usuario
exports.UserInfo = (req, res) => {
    if (!req.body.nombre || !req.body.dpi || !req.body.base64) {
        return res.status(400).json({ message: "Se enviaron datos incompletos." });
    }

    let imagen = req.body.dpi + req.body.base64.substring(30, 40)+".jpg";
    persona.dpi = req.body.dpi;
    persona.nombre = req.body.nombre;
    persona.imagen = "    https://arq2p2.s3.us-east-2.amazonaws.com/fotos/"+imagen

    var decodedImage = new Buffer(req.body.base64.replace('data:image/jpeg;base64,',''), 'base64');
    let parametros = {
        Bucket: "arq2p2",
        Key: "fotos/" + imagen,
        Body: decodedImage
    }

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
    if(persona.nombre == null){
        return res.status(400).json({ message: "Antes de medir la temperatura "+
            "se deben tomar los datos de la persona." });
    }
    if (!req.body.temperatura) {
        return res.status(400).json({ message: "No se envio la temperatura" });
    }

    persona.temperatura = req.body.temperatura

    Persona.create(persona, (err, persona) => {
            if (err) {
                return res.status(500).json({
                    db_message: err.message || "",
                    message: "Error al guardar al usuario"
                });
            }
            return res.status(200).json({
                producto: persona,
                message: "Usuario agregado"
            });
        });
};


// Obtener todos los productos
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