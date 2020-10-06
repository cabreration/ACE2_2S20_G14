module.exports = mongoose => {
  var schema = mongoose.Schema(
    {
      peso_paquete: { type: Number, required: true }, 
      dia_entrega: { type: String, required: true }, 
      hora_entrega: { type: Number, required: true },
      obstaculos_ida: { type: Number, required: true },
      obstaculos_regreso: { type: Number, required: true },
      tiempo_ida: { type: Number, required: true },
      tiempo_regreso: { type: Number, required: true },
      _id: Object
    },
    { timestamps: true }
  );

  schema.method("toJSON", function () {
    const { __v, _id, ...object } = this.toObject();
    object.id = _id;
    return object;
  });

  const Entregas = mongoose.model("entregas", schema);
  return Entregas;
};