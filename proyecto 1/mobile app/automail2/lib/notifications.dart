import 'dart:async';
import 'dart:io';

import 'package:firebase_messaging/firebase_messaging.dart';

class NotificationProvider {
  FirebaseMessaging _firebaseMessaging = FirebaseMessaging();

  final _mensajesStreamController = StreamController<String>.broadcast();

  Stream<String> get mensajes => _mensajesStreamController.stream;
  NotificationProvider() {
    _firebaseMessaging.requestNotificationPermissions();
    /*
      _firebaseMessaging.getToken().then((token) {
        print('----token----');
        print(token);
      });
    */

    _firebaseMessaging.configure(
      onMessage: (Map<String, dynamic> message) async {
        String argumento = 'no-data';
        if (Platform.isAndroid) {
          argumento = message['data']['msj'] ?? 'no-data';
        }
        _mensajesStreamController.sink.add(argumento);
        dispose();
      },
      onLaunch: (Map<String, dynamic> message) async {
        print("onLaunch: $message");
        dispose();
      },
      onResume: (Map<String, dynamic> message) async {
        print("onResume: $message");
        dispose();
      },
    );
  }

  obtenerMensaje() {
    String notificacion="";
    mensajes.listen((mensaje) {
      notificacion = mensaje;
    });
    return notificacion;
  }

  dispose() {
    _mensajesStreamController?.close();
  }
}
