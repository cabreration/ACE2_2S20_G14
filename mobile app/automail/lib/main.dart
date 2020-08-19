import 'package:flutter/painting.dart';
import 'package:flutter/rendering.dart';
import 'package:http/http.dart' as http;
import 'Slider/Slider.dart' as mySlider;
import 'network.dart';
import 'notifications.dart';
import 'dart:ui' as ui;

/*import 'package:flutter/material.dart';
import 'package:http/http.dart' as http;

void main() => runApp(MaterialApp(home: MyApp()));


class MyApp extends StatelessWidget{

  @override
  Widget build(BuildContext context) {
    return Scaffold(
      appBar: AppBar(title: Text("Un texto")
      ), body: miprueba(),
    );
  }
}

class miprueba extends StatelessWidget {
  var url = "URL de la peticion";

  Future<String> pedirDatos() async{
    var respuesta = await http.get(url);
    print(respuesta.body);
  }

/*
  @override
  Widget build(BuildContext context) {
    return Center(
      child: RaisedButton(child: Text("obtener datos"), onPressed: (){pedirDatos(); } ),);
  }
*/

  @override
  Widget build(BuildContext context) {
    return Scaffold(
      body: Center(
        child: RangeSlider(
          min: 1,
          max: 100,
          divisions: 2,
        ),
      )
    );
  }
}
*/
// Flutter code sample for Slider

// ![A slider widget, consisting of 5 divisions and showing the default value
// indicator.](https://flutter.github.io/assets-for-api-docs/assets/material/slider.png)
//
// The Sliders value is part of the Stateful widget subclass to change the value
// setState was called.
import 'dart:math';

import 'package:flutter/material.dart';

import 'Slider/Slider.dart';

List<int> bars = [];
const barWidth = 5.0;
double screenWidth;
int numberOfBars;

void main() {
  runApp(MyApp());
}

class MyApp extends StatelessWidget {
  @override
  Widget build(BuildContext context) {
    return MaterialApp(
      title: "Automail",
      home: Scaffold(
        appBar: AppBar(
          title: Text("Automail"),
          backgroundColor: Colors.orange,
        ),
        body: Column(
          children: [Body()],
        ),
      ),
    );
  }
}

class Body extends StatefulWidget {
  @override
  State<StatefulWidget> createState() {
    final notifications = new NotificationProvider();
    notifications.initNotificacions();
    return PageBody();
    //throw UnimplementedError();
  }
}

class PageBody extends State<Body> {
  double width;
  @override
  Widget build(BuildContext context) {
    width = MediaQuery.of(context).size.width;
    mySlider.WaveSlider().generateBar(width - 25);
    peticiones().then((value) => print(value.toString()));
    //throw UnimplementedError();
    return Container(
      child: FutureBuilder<Widget>(
        future: peticiones(), // a previously-obtained Future<String> or null
        builder: (BuildContext context, AsyncSnapshot<Widget> snapshot) {
          List<Widget> children;
          if (snapshot.hasData) {
            children = <Widget>[
              Icon(
                Icons.check_circle_outline,
                color: Colors.black45,
                size: 60,
              ),
              Padding(
                padding: const EdgeInsets.only(top: 16),
                child: snapshot.data,
              )
            ];
          } else if (snapshot.hasError) {
            children = <Widget>[
              Icon(
                Icons.error_outline,
                color: Colors.red,
                size: 60,
              ),
              Padding(
                padding: const EdgeInsets.only(top: 16),
                child: Text('Error: ${snapshot.error}'),
              )
            ];
          } else {
            children = <Widget>[
              SizedBox(
                child: CircularProgressIndicator(),
                width: 60,
                height: 60,

              ),
              const Padding(
                padding: EdgeInsets.only(top: 16),
                child: Text('Awaiting result...'),
              )
            ];
          }
          return Center(
            child: Column(
              mainAxisAlignment: MainAxisAlignment.center,
              crossAxisAlignment: CrossAxisAlignment.center,
              children: children,
            ),
          );
        },
      ),
      color: Colors.black54,
    );
  }

  Future<Widget> peticiones() async {
    //var response = await http
    //    .get('http://18.188.92.62:3000/mail');
    //var dat = response.body;
    //return Text('Tesultado $response.body.');
    return Container(
      child: Column(
        children: [
          Text(""),
          Text(""),
          Center(
            child: Card(
              child: InkWell(
                splashColor: Colors.blue.withAlpha(30),
                onTap: () {
                  print('Card tapped.');
                },
                child: Container(
                  width: width - 26,
                  height: 122,
                  child: Column(
                    children: [
                      Text(""),
                      Text(
                        "50",
                        style: TextStyle(fontStyle: FontStyle.italic),
                      ),
                      mySlider.WaveSlider(),
                    ],
                  ),
                ),
              ),
            ),
          ),
          Text(""),
          Text(""),
          Text(""),
          Text(""),
          Text(""),
          Center(
            child: Card(
              child: InkWell(
                splashColor: Colors.blue.withAlpha(30),
                onTap: () {
                  print('Card tapped.');
                },
                child: Container(
                  width: width - 26,
                  height: 120,
                  child: Column(
                    children: [
                      Text(""),
                      Text(
                        "50",
                        style: TextStyle(fontStyle: FontStyle.italic),
                      ),
                      Text(""),
                      Ink(
                        decoration: const ShapeDecoration(
                          color: Colors.lightGreen,
                          shape: CircleBorder(),
                        ),
                        child: IconButton(
                          icon: Icon(Icons.shopping_basket),
                          color: Colors.white70,
                          onPressed: () {},
                        ),
                      ),
                    ],
                  ),
                ),
              ),
            ),
          ),
          Text(""),
          Text(""),
          Text(""),
          Text(""),
          Text(""),
          Center(
            child: Card(
              child: InkWell(
                splashColor: Colors.blue.withAlpha(30),
                onTap: () {
                  print('Card tapped.');
                },
                child: Container(
                  width: width - 26,
                  height: 105,
                  child: Column(
                    children: [
                      Text(
                        'Un paquete se encuentra en el buzon.',
                        style: TextStyle(
                            fontSize: 14,
                            foreground: Paint()
                              ..shader = ui.Gradient.linear(
                                const Offset(0, 20),
                                const Offset(150, 20),
                                <Color>[
                                  Colors.blue,
                                  Colors.green,
                                ],
                              )
                        ),
                      ),
                      Text(
                        'El nivel de desinfectante es menor del 10%.',
                        style: TextStyle(
                            fontSize: 14,
                            foreground: Paint()
                              ..shader = ui.Gradient.linear(
                                const Offset(0, 20),
                                const Offset(150, 20),
                                <Color>[
                                  Colors.redAccent,
                                  Colors.yellow,
                                ],
                              )
                        ),
                      ),
                      Text(
                        'El desinfectante se agoto.',
                        style: TextStyle(
                            fontSize: 14,
                            foreground: Paint()
                              ..shader = ui.Gradient.linear(
                                const Offset(0, 20),
                                const Offset(150, 20),
                                <Color>[
                                  Colors.red,
                                  Colors.deepOrange,
                                ],
                              )
                        ),
                      ),
                    ],
                    crossAxisAlignment: CrossAxisAlignment.start,
                  ),
                ),
              ),
            ),
          ),
          Text(""),
          Text(""),
          Text(""),
          Text(""),
          Text(""),
        ],
      ),
    );
  }
/*
  Future<Widget> peticiones() async{
    var response = await http
        .get(Uri.encodeFull("http://18.188.92.62:3000/mail"));

    return Text('Tesultado $response.body');
  }*/
}
