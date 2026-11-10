
function coincide(nombre, filtro) {
    return new RegExp(filtro).test(nombre);
}
module.exports = { coincide };
