const origen = {
    demand: true,
    alias: 'o',
    desc: 'Origen del Archivo, Ruta Completa'
};
const destino = {
    default: true,
    alias: 'd',
    desc: 'Destino del Archivo, Ruta Completa'
}

const tipo = {
    default: 'texto',
    alias: 't',
    desc: `Tipo, para encriptar o desencriptar, Opciones: "texto" (Default) los archivos javascript se consideran texto \n ,"json" (Formato json).`
};


const argv = require('yargs')
    .command('cripto', 'Encripta un archivo ', {
        origen,
        destino,
        tipo
    })
    .command('decripto', 'Desencripta un Archivo', {
        origen,
        destino,
        tipo
    })
    .help()
    .argv;


module.exports = {
    argv
}