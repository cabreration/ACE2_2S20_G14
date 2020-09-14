import 'package:flutter/material.dart';
import 'dart:convert';
import 'package:http/http.dart' as http;
/*
Future<Widget> peticiones() async{
  var response = await http
      .get(Uri.encodeFull("http://18.188.92.62:3000/mail"));

  return Text('Tesultado $response.body');
}*/


Future<Map> peticiones() async {
  try {
    var response = await http.get('http://18.188.92.62:3000/mail');
    Map data = json.decode(response.body);
    return data;
  }
  catch(x){
    return null;
  }
}