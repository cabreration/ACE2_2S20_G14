import 'package:flutter/painting.dart';
import 'package:flutter/rendering.dart';
import 'package:http/http.dart' as http;
import 'Slider/Slider.dart' as mySlider;
import 'network.dart';
import 'notifications.dart';
import 'dart:ui' as ui;
import 'package:flutter/material.dart';
import 'dart:async';
import 'dart:convert';
import 'package:flutter/services.dart';

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
      debugShowCheckedModeBanner: false,
      title: "Automail",
      home: Scaffold(
        appBar: AppBar(
          title: Text("Automail"),
          backgroundColor: Colors.orange,
        ),
        body: Column(
          children: [Body()],
        ),
        //  backgroundColor: Colors.black12,
      ),
    );
  }
}

var icono = IconButton(
  icon: Icon(Icons.shopping_basket),
  color: Colors.lightGreen,
  onPressed: () {},
);
var notificacionVerde = Text(
  'Un paquete se encuentra en el buzon.',
  style: TextStyle(
      fontSize: 14,
      foreground: Paint()
        ..shader = ui.Gradient.linear(
          const Offset(0, 20),
          const Offset(150, 20),
          <Color>[
            Colors.black38,
            Colors.grey,
          ],
        )),
);
var notificacionAnaranjada = Text(
  'El nivel de desinfectante es menor del 10%.',
  style: TextStyle(
      fontSize: 14,
      foreground: Paint()
        ..shader = ui.Gradient.linear(
          const Offset(0, 20),
          const Offset(150, 20),
          <Color>[
            Colors.black38,
            Colors.grey,
          ],
        )),
);
var notificacionRoja = Text(
  'El desinfectante se agoto.',
  style: TextStyle(
      fontSize: 14,
      foreground: Paint()
        ..shader = ui.Gradient.linear(
          const Offset(0, 20),
          const Offset(150, 20),
          <Color>[
            Colors.black38,
            Colors.grey,
          ],
        )),
);

int nivelDesnfectante = 0;
int pesoObjeto = 0;

class Body extends StatefulWidget {
  @override
  State<StatefulWidget> createState() {
    return PageBody();
  }
}

class PageBody extends State<Body> {
  double width;
  double widthCards;

  @override
  Widget build(BuildContext context) {
    const fiveSeconds = const Duration(seconds: 10);
    final notifications = new NotificationProvider();
    notifications.initNotificacions();
    notifications.mensajes.listen((argumento) {
      print("contenido del mensaje");
      print(argumento);
      switch (argumento) {
        case "notificacion1":
          notificacionVerde = Text(
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
                  )),
          );
          break;
        case "notificacion2":
          notificacionAnaranjada = Text(
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
                  )),
          );
          break;
        case "notificacion3":
          notificacionRoja = Text(
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
                  )),
          );
      }
      setState(() {});
    });

    width = MediaQuery.of(context).size.width;
    widthCards = width - 25;
    mySlider.WaveSlider().generateBar(width - 25);
    var data = Timer.periodic(fiveSeconds, (Timer t) => peticiones().then((value) => print(value.toString())));

    return Container(
      color: Colors.black45,
      child: Column(
        children: [
          Text(""),
          Text(""),
          Center(
            child: Card(
              child: InkWell(
                splashColor: Colors.blue.withAlpha(30),
                onTap: () {
                  mySlider.WaveSlider().mover((nivelDesnfectante.toDouble()*20));
                  setState(() {

                  });
                },
                child: Container(
                  width: widthCards,
                  height: 122,
                  child: Column(
                    children: [
                      Text(""),
                      Text(
                        nivelDesnfectante.toString(),
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
                  icono = IconButton(
                    icon: Icon(Icons.shopping_basket),
                    color: Colors.white70,
                    onPressed: () {},
                  );
                  setState(() {});
                },
                child: Container(
                  width: widthCards,
                  height: 120,
                  child: Column(
                    children: [
                      Text(""),
                      Text(
                        pesoObjeto.toString(),
                        style: TextStyle(fontStyle: FontStyle.italic),
                      ),
                      Text(""),
                      Ink(
                        decoration: const ShapeDecoration(
                          color: Colors.lightGreen,
                          shape: CircleBorder(),
                        ),
                        child: icono,
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
                  notificacionVerde = Text(
                    'Un paquete se encuentra en el buzon.',
                    style: TextStyle(
                        fontSize: 14,
                        foreground: Paint()
                          ..shader = ui.Gradient.linear(
                            const Offset(0, 20),
                            const Offset(150, 20),
                            <Color>[
                              Colors.black38,
                              Colors.grey,
                            ],
                          )),
                  );
                  notificacionAnaranjada = Text(
                    'El nivel de desinfectante es menor del 10%.',
                    style: TextStyle(
                        fontSize: 14,
                        foreground: Paint()
                          ..shader = ui.Gradient.linear(
                            const Offset(0, 20),
                            const Offset(150, 20),
                            <Color>[
                              Colors.black38,
                              Colors.grey,
                            ],
                          )),
                  );
                  notificacionRoja = Text(
                    'El desinfectante se agoto.',
                    style: TextStyle(
                        fontSize: 14,
                        foreground: Paint()
                          ..shader = ui.Gradient.linear(
                            const Offset(0, 20),
                            const Offset(150, 20),
                            <Color>[
                              Colors.black38,
                              Colors.grey,
                            ],
                          )),
                  );

                  setState(() {});
                },
                child: Container(
                  width: widthCards,
                  height: 120,
                  padding: EdgeInsets.all(16.0),
                  child: Column(
                    children: [
                      notificacionVerde,
                      notificacionAnaranjada,
                      notificacionRoja,
                    ],
                    crossAxisAlignment: CrossAxisAlignment.start,
                  ),
                ),
              ),
            ),
          ),
          Text(""),
          Text(""),
          //Text(""),
        ],
      ),
    );
  }

  peticiones() async {
    var response = await http.get('http://18.188.92.62:3000/mail');
    Map data = json.decode(response.body);
    pesoObjeto = data["peso"];
    nivelDesnfectante = data["liquido"];
    mySlider.WaveSlider().mover(nivelDesnfectante.toDouble());
    if(pesoObjeto==0){
      icono = IconButton(
        icon: Icon(Icons.shopping_basket),
        color: Colors.lightGreen,
        onPressed: () {},
      );
    }else{
      icono = IconButton(
        icon: Icon(Icons.shopping_basket),
        color: Colors.white,
        onPressed: () {},
      );
    }
    setState(() {

    });
  }
}
