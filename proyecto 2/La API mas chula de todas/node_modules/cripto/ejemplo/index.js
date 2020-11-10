'use strict'
    const argv = require('./config/yargs').argv
    const fs = require('fs')
    const { cripto } = require('@lbricenoyts/cripto')

    let comando = argv._[0];

    switch (comando) {
        case 'cripto':
                Encripta()
            break;
        case 'decripto':
                Decripta()
            break;
        default:
            console.log("No se encuentra la opción, utilice --help");
            break;
    }

    function Decripta(){
        let archivo = fs.readFileSync(argv.origen);
        const tipo = argv.tipo;
        let datos;
        switch (tipo) {
            case "json":
                console.log("Sedencriptando Objeto ...");
                datos = cripto.toObj(`${archivo}`)
                break;
            default:
                console.log("Desencriptando Otro ...");
                datos = cripto.toText(`${archivo}`)
                break;
        }

        fs.writeFile(argv.destino, datos, (err) => {
            if (err) {
                console.log('Hubo un error al Escribir el archivo')
                console.log(err)
                return
            }
            console.log(`Se guardó ${argv.destino}: Correctamente `)
        })   
    }

    function Encripta(){
        let archivo =fs.readFileSync(argv.origen);
        const tipo = argv.tipo;
        let datos;
        switch (tipo) {
            case "json":
                console.log("Encriptando Objeto ...");
                datos = cripto.toCodeObj(`${archivo}`)
                break;
            
            default:
                console.log("Encriptando Otro ...");
                datos = cripto.toCode(`${archivo}`)
                break;
        }
         
        fs.writeFile(argv.destino, datos, (err) => {
            if (err) {
                console.log('Hubo un error al Escribir el archivo')
                console.log(err)
                return
            }
            console.log(`Se guardó ${argv.destino}: Correctamente `)
        })    
    }