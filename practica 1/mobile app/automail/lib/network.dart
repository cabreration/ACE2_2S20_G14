import 'package:flutter/material.dart';
import 'package:http/http.dart' as http;

Future<Widget> peticiones() async{
  var response = await http
      .get(Uri.encodeFull("http://18.188.92.62:3000/mail"));

  return Text('Tesultado $response.body');
}