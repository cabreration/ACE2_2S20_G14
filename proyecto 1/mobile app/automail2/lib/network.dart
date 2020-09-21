import 'package:flutter/material.dart';
import 'dart:convert';
import 'package:http/http.dart' as http;
/*
Future<Widget> peticiones() async{
  var response = await http
      .get(Uri.encodeFull("http://18.188.92.62:3000/mail"));

  return Text('Tesultado $response.body');
}*/

Map<String, String> data = {
  'avg_go': "00",
  'avg_come': "00",
  'total_obstacles': "00",
  'avg_weight': "00",
  'total_delivered': "00",
  'x_axis': "00",
  'y_axis': "00"
};

Future<Map> peticiones() async {
  try {
    var response = await http.get('http://18.188.84.47:3000/data');
    Map values = json.decode(response.body);

    if (values != null) {
      data["avg_go"] = values["avg_go"];
      data["avg_come"] = values["avg_come"];
      data["total_obstacles"] = values["total_obstacles"];
      data["avg_weight"] = values["avg_weight"];
      data["total_delivered"] = values["total_delivered"];

      if(data["x_axis"] != values["x_axis"]){
        data["x_axis"] = values["x_axis"];
      }

      if(data["y_axis"] != values["y_axis"]){
        data["y_axis"] = values["y_axis"];
      }
    }

    return data;
  } catch (x) {
    print(x);
    return data;
  }
}

Future<Map> CambiarEstado(bool estado) async {
  try {
    Map<String, String> headers = {'Content-Type': 'application/json'};
    final body = jsonEncode({"estado": estado ? "i" : "a"});

    var response = await http.post('http://18.188.84.47:3000/switch',
        headers: headers, body: body);
    print(response.body);
  } catch (x) {
    print(x);
  }
}
