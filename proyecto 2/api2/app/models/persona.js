module.exports = mongoose => {
  var schema = mongoose.Schema(
    {
      nombre: { type: String, required: true },
      dpi: { type: Number, required: true },
      temperatura: { type: Number, required: true },
      tiempo: { type: Number, required: true },
      imagen: { type: String, required: true },
      fecha: { type: String, required: true },
      hora: { type: String, required: true }
    },
    { timestamps: true }
  );

  schema.method("toJSON", function () {
    const { __v, _id, ...object } = this.toObject();
    object.id = _id;
    return object;
  });

  const Persona = mongoose.model("persona", schema);
  return Persona;
};