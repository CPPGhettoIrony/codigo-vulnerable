

function actualizar(config, entrada) {
    for (const clave of Object.keys(entrada)) {
        config[clave] = entrada[clave];
    }
    return config;
}
module.exports = { actualizar };
