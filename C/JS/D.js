
function actualizar(config, entrada) {
    if (!entrada || typeof entrada !== "object" || Array.isArray(entrada)) {
        throw new Error("Objeto requerido");
    }
    for (const clave of Object.keys(entrada)) {
        if (clave !== "nombre" && clave !== "activo") throw new Error("Clave");
    }
    if (Object.hasOwn(entrada, "nombre")) {
        if (typeof entrada.nombre !== "string" || entrada.nombre.length > 64) throw new Error("Nombre");
        config.nombre = entrada.nombre;
    }
    if (Object.hasOwn(entrada, "activo")) {
        if (typeof entrada.activo !== "boolean") throw new Error("Activo");
        config.activo = entrada.activo;
    }
    return config;
}
module.exports = { actualizar };
