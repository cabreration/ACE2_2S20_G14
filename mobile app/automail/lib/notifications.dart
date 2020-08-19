import 'dart:async';
import 'dart:io';

import 'package:firebase_messaging/firebase_messaging.dart';


class NotificationProvider{

  FirebaseMessaging _firebaseMessaging = FirebaseMessaging();

  final _mensajesStreamController = StreamController<String>.broadcast();

  Stream<String> get mensajes => _mensajesStreamController.stream;

  initNotificacions(){
    _firebaseMessaging.requestNotificationPermissions();
    _firebaseMessaging.getToken().then((token) {
      print('----token----');
      print(token);
      //ccTZYNoCQISzt7j3ETfjYp:APA91bEZgzSF76B4JRRNBPHogKOo2np64qcQ_kB-3l4pzgsQymorhBJAxO3uV8C13Zw0HnMSPj4zYlqFv9cc4Ictjz9-YDJApUxZ9ZP7dGySNpgNIZBc5FBH2gLmv29-wFiT5fViJ_k6
    });

    _firebaseMessaging.configure(
      onMessage: (Map<String, dynamic> message) async {
        print("onMessage: $message");

        String argumento = 'no-data';
        if(Platform.isAndroid){
          argumento = message['data']['msj'] ?? 'no-data';
        }
        _mensajesStreamController.sink.add(argumento);
      },
      onLaunch: (Map<String, dynamic> message) async {
        print("onLaunch: $message");
      },
      onResume: (Map<String, dynamic> message) async {
        print("onResume: $message");
        final noti = message['data']['comida'];
        print("------------------"+noti+"-----------------");
      },
    );

  }

  dispose(){
    _mensajesStreamController?.close();
  }

}