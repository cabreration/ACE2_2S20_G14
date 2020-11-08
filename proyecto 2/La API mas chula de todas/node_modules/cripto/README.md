# cripto
Pruebas de Criptografía

para utilizar el módulo de manera regular.

> Se debe instalar como un módulo cualquiera, especificar la ruta: <ruta-completa> 

```bash
    npm install https://github.com/lbricenoyts/cripto/archive/v0.2.2.tar.gz
```

> Probamos con un texto de prueba
```javascript
    const { cripto } = require('@lbricenoyts/cripto')

    // Encriptado de texto 
    let encriptado = cripto.toCode("Texto de Prueba")
    console.log('encriptado',encriptado)
    let texto = cripto.toText(encriptado)
    console.log('desencriptado',texto)

```

> Trabajar con archivos.

Escribimos un Archivo:

/archivos/objeto1.json
```json
{
    "nombre":"Luis Delfin",
    "email": "luis.delfin.bg@gmail.com"
}
```

index.js
```javascript
    'use strict'
    const fs = require('fs')
    const { cripto } = require('@lbricenoyts/cripto')

    // Cargamos el Archivo con formato json
    const archivo = require('./archivos/objeto1.json')

    // Elegimos el destino
    const destino = "./destino/encriptado1.txt"

    // Encriptamos
    const datos = cripto.toCodeObj(archivo)

    // Escribios el archivo encriptado en destino
    fs.writeFile(destino, datos, (err) => {
        if (err) {
            console.log('Hubo un error al Escribir el archivo')
            console.log(err)
            return
        }
        console.log('se escribió el archivo correctamente')
    })

    // Desencriptado de Archivos
    fs.readFile(destino, (err, data) => {
        if (err) {
            console.log('Hubo un error al tratar de lleer el archivo')
            console.log(err)
            return
        }

        // Mostramos el contenido sin desencriptar
        console.log(data)
        
        // Desencriptamos el Archivo a un Objeto
        const decriptoFile = cripto.toObj(data);
        console.log(decriptoFile);
    })
```

