import 'dart:async';
import 'dart:convert';
import 'package:flutter/material.dart';
import 'network.dart';
import 'notifications.dart';

class Dashboard extends StatefulWidget {
  @override
  _DashboardState createState() => _DashboardState();
}

class _DashboardState extends State<Dashboard> {
  @override
  Widget build(BuildContext context) {
    final notifications = new NotificationProvider();
    notifications.mensajes.listen((data) {
      mensaje = data.replaceAll("\"", "");
      setState(() {});
    });
    const seconds = const Duration(seconds: 30);
    Timer.periodic(
        seconds, (Timer t) => peticiones().then((value) => setState(() {})));

    return Scaffold(
      appBar: AppBar(
        title: Text("Automail2"),
        elevation: .1,
        backgroundColor: Colors.white,
      ),
      body: Container(
        padding: EdgeInsets.symmetric(vertical: 10.0, horizontal: 2.0),
        child: GridView.count(
          crossAxisCount: 2,
          padding: EdgeInsets.all(3.0),
          children: <Widget>[
            makeDashboardItem("Peso promedio", data["avg_weight"].toString(),
                Icons.dehaze, Color.fromRGBO(153, 51, 255, 1)),
            makeDashboardItem("Obstaculos detectados", data["total_obstacles"],
                Icons.call_split, Color.fromRGBO(255, 51, 153, 1)),
            makeDashboardItem("Tiempo regreso promedio", data["avg_come"],
                Icons.hourglass_full, Color.fromRGBO(0, 102, 204, 1)),
            makeDashboardItem("Tiempo entrega promedio", data["avg_go"],
                Icons.hourglass_empty, Color.fromRGBO(128, 128, 128, 1)),
            makeDashboardItem("Paquetes entregados", data["total_delivered"],
                Icons.redeem, Color.fromRGBO(0, 204, 204, 1)),
            makeDashboardItemState(),
            makeDashboardItemCanvas(
                double.parse(data["x_axis"]), double.parse(data["x_axis"])),
            makeDashboardItemnNotficacion(
                "Notificaciones", mensaje, Colors.orange),
          ],
        ),
      ),
      backgroundColor: Color.fromRGBO(0, 0, 0, 1.0),
    );
  }

  Color _colorActive = Color.fromRGBO(76, 153, 0, 1);
  String _activeInactiveState = "Activo";
  bool _stateState = false;
  Card makeDashboardItemState() {
    return Card(
        elevation: 1.0,
        margin: new EdgeInsets.all(8.0),
        child: Container(
          decoration: BoxDecoration(color: _colorActive),
          child: new InkWell(
            onTap: () {
              _stateState = !_stateState;
              if (_stateState) {
                _colorActive = Color.fromRGBO(204, 0, 0, 1);
                _activeInactiveState = "Inactivo";
              } else {
                _colorActive = Color.fromRGBO(76, 153, 0, 1);
                _activeInactiveState = "Activo";
              }

              CambiarEstado(_stateState);

              setState(() {});
            },
            child: Column(
              crossAxisAlignment: CrossAxisAlignment.stretch,
              mainAxisSize: MainAxisSize.min,
              verticalDirection: VerticalDirection.down,
              children: <Widget>[
                SizedBox(height: 10.0),
                new Center(
                  child: new Text("Estado del vehiculo",
                      textAlign: TextAlign.center,
                      style:
                          new TextStyle(fontSize: 14.0, color: Colors.white)),
                ),
                SizedBox(height: 20.0),
                Center(
                    child: Icon(
                  Icons.directions_car,
                  size: 40.0,
                  color: Colors.white,
                )),
                SizedBox(height: 20.0),
                new Center(
                  child: new Text(_activeInactiveState,
                      textAlign: TextAlign.center,
                      style:
                          new TextStyle(fontSize: 30.0, color: Colors.white)),
                )
              ],
            ),
          ),
        ));
  }

  Card makeDashboardItem(
      String title, String textItem, IconData icon, Color color) {
    return Card(
        elevation: 1.0,
        margin: new EdgeInsets.all(8.0),
        child: Container(
          decoration: BoxDecoration(color: color),
          child: new InkWell(
            onTap: () {},
            child: Column(
              crossAxisAlignment: CrossAxisAlignment.stretch,
              mainAxisSize: MainAxisSize.min,
              verticalDirection: VerticalDirection.down,
              children: <Widget>[
                SizedBox(height: 10.0),
                new Center(
                  child: new Text(title,
                      textAlign: TextAlign.center,
                      style:
                          new TextStyle(fontSize: 14.0, color: Colors.white)),
                ),
                SizedBox(height: 20.0),
                Center(
                    child: Icon(
                  icon,
                  size: 40.0,
                  color: Colors.white,
                )),
                SizedBox(height: 20.0),
                new Center(
                  child: new Text(textItem,
                      textAlign: TextAlign.center,
                      style:
                          new TextStyle(fontSize: 30.0, color: Colors.white)),
                )
              ],
            ),
          ),
        ));
  }

  String mensaje = "";
  Card makeDashboardItemnNotficacion(
      String title, String textItem, Color color) {
    return Card(
        elevation: 1.0,
        margin: new EdgeInsets.all(8.0),
        child: Container(
          decoration: BoxDecoration(color: color),
          child: new InkWell(
            onTap: () {
              mensaje = "";
              setState(() {});
            },
            child: Column(
              crossAxisAlignment: CrossAxisAlignment.stretch,
              mainAxisSize: MainAxisSize.min,
              verticalDirection: VerticalDirection.down,
              children: <Widget>[
                SizedBox(height: 10.0),
                new Center(
                  child: new Text(title,
                      textAlign: TextAlign.center,
                      style:
                          new TextStyle(fontSize: 14.0, color: Colors.white)),
                ),
                SizedBox(height: 30.0),
                new Center(
                  child: new Text(textItem,
                      textAlign: TextAlign.center,
                      style:
                          new TextStyle(fontSize: 12.0, color: Colors.white)),
                )
              ],
            ),
          ),
        ));
  }

  Card makeDashboardItemCanvas(double posX, double posY) {
    double _posX = 19 + (posX * 0.2667);
    double _posY = 20 + (posY * 0.994);
    return Card(
      elevation: 1.0,
      margin: new EdgeInsets.all(8.0),
      child: Container(
        // pass double.infinity to prevent shrinking of the painter area to 0.
        width: double.infinity,
        height: double.infinity,
        color: Colors.yellow,
        child: CustomPaint(painter: FaceOutlinePainter(_posX, _posY)),
      ),
    );
  }

/*
  Future<String> peiciones() async {
    try {
      Map data = peticiones();
      pesoObjeto =  int.parse(data["peso"]);
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
    }catch(x){
      pesoObjeto = 0;
      nivelDesnfectante = 0;
      icono = IconButton(
        icon: Icon(Icons.shopping_basket),
        color: Colors.lightGreen,
        onPressed: () {},
      );
    }

    setState(() {

    });
    return "";
  }*/
}

class FaceOutlinePainter extends CustomPainter {
  double _posX, _posY;

  set posY(value) {
    _posY = value;
  }

  set posX(value) {
    _posX = value;
  }

  FaceOutlinePainter(double _posX, double _posY) {
    this._posX = _posX;
    this._posY = _posY;
  }

  @override
  void paint(Canvas canvas, Size size) {
    // Define a paint object
    final paint = Paint()
      ..style = PaintingStyle.stroke
      ..strokeWidth = 20
      ..color = Colors.indigo;

    // Mouth
    final mouth = Path();
    mouth.moveTo(20, 170);
    mouth.lineTo(20, 10);
    mouth.moveTo(10, 170);
    mouth.lineTo(170, 170);

    canvas.drawPath(mouth, paint);

    final paintWhite = Paint()
      ..style = PaintingStyle.stroke
      ..strokeWidth = 10
      ..color = Colors.white;

    // Mouth
    final mouthPoint = Path();
    mouthPoint.addOval(Rect.fromLTWH(_posX, _posY, 2, 2));

    canvas.drawPath(mouthPoint, paintWhite);
  }

  @override
  bool shouldRepaint(FaceOutlinePainter oldDelegate) => true;
}
