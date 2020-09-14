import 'package:flutter/material.dart';
import 'network.dart';

class Dashboard extends StatefulWidget {
  @override
  _DashboardState createState() => _DashboardState();
}

class _DashboardState extends State<Dashboard> {
  @override
  Widget build(BuildContext context) {
    return Scaffold(
      appBar: AppBar(
        title: Text("Automail2"),
        elevation: .1,
        backgroundColor: Color.fromRGBO(0, 0, 0, 1.0),
      ),
      body: Container(
        padding: EdgeInsets.symmetric(vertical: 10.0, horizontal: 2.0),
        child: GridView.count(
          crossAxisCount: 2,
          padding: EdgeInsets.all(3.0),
          children: <Widget>[
            makeDashboardItem("Peso promedio", Icons.alarm,
                Color.fromRGBO(153, 51, 255, 1)),
            makeDashboardItem("Obstaculos detectados", Icons.alarm,
                Color.fromRGBO(255, 51, 153, 1)),
            makeDashboardItem("Tiempo regreso promedio", Icons.alarm,
                Color.fromRGBO(0, 102, 204, 1)),
            makeDashboardItem("Tiempo entrega promedio", Icons.alarm,
                Color.fromRGBO(128, 128, 128, 1)),
            makeDashboardItem("Paquetes entregados", Icons.book,
                Color.fromRGBO(0, 204, 204, 1)),
            makeDashboardItem(
                "Activar", Icons.alarm, Color.fromRGBO(76, 153, 0, 1)),
            makeDashboardItemBar(
                "Posicion", Icons.alarm, Color.fromRGBO(76, 153, 0, 1)),
          ],
        ),
      ),
    );
  }

  Card makeDashboardItem(String title, IconData icon, Color color) {
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
                  child: new Text("---- 50 ----",
                      textAlign: TextAlign.center,
                      style:
                          new TextStyle(fontSize: 30.0, color: Colors.white)),
                )
              ],
            ),
          ),
        ));
  }

  Card makeDashboardItemBar(String title, IconData icon, Color color) {
    return Card(
      elevation: 1.0,
      margin: new EdgeInsets.all(8.0),
      child: Container(
        // pass double.infinity to prevent shrinking of the painter area to 0.
        width: double.infinity,
        height: double.infinity,
        color: Colors.yellow,
        child: CustomPaint(painter: FaceOutlinePainter()),
      ),
    );
  }


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
  }
}

class FaceOutlinePainter extends CustomPainter {
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
  }

  @override
  bool shouldRepaint(FaceOutlinePainter oldDelegate) => false;
}
