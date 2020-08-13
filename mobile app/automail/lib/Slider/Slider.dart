import 'dart:math';

import 'package:flutter/material.dart';

List<int> bars = [];
const barWidth = 5.0;
int numberOfBars;

void randomNumberGenerator() {
  for (var i = 0; i < numberOfBars; i++) {
    bars.add(10 + i);
  }
}

class WaveSlider extends StatefulWidget {
  @override
  State<StatefulWidget> createState() => WaveSliderState();

  // ignore: non_constant_identifier_names
  void generateBar(double screenWidth) {
    //if (bars.isEmpty) {
    //screenWidth = MediaQuery.of(context).size.width;
    numberOfBars = screenWidth ~/ barWidth;
    randomNumberGenerator();
    //}
  }
}

class WaveSliderState extends State<WaveSlider> {
  double bar2Position = 0;

  _onTapDown(TapDownDetails details) {
    var x = details.globalPosition.dx;
    print("tap down " + x.toString());
    setState(() {
      bar2Position = x;
    });
  }

  @override
  Widget build(BuildContext context) {
    int barItem = 0;
    return Scaffold(
      body: Center(
        child: Stack(
          alignment: Alignment.centerLeft,
          children: <Widget>[
            GestureDetector(
              onTapDown: (TapDownDetails details) => _onTapDown(details),
              onHorizontalDragUpdate: (DragUpdateDetails details) {
                setState(() {
                  bar2Position = details.globalPosition.dx;
                });
              },
              child: Container(
                child: Row(
                  crossAxisAlignment: CrossAxisAlignment.end,
                  mainAxisAlignment: MainAxisAlignment.start,
                  children: bars.map((int height) {
                    Color color;
                    if (barItem + 1 < bar2Position / barWidth) {
                      if (barItem + 1 < 11) {
                        color = Colors.red;
                      } else if (barItem + 1 < 51) {
                        color = Colors.yellow;
                      } else {
                        color = Colors.green;
                      }
                    } else {
                      color = Colors.grey;
                    }
                    barItem++;
                    return Container(
                      color: color,
                      height: height.toDouble(),
                      width: 5,
                    );
                  }).toList(),
                ),
              ),
            ),
          ],
        ),
      ),
    );
  }
}
