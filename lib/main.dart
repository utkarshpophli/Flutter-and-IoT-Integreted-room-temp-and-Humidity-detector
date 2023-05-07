import 'package:firebase_core/firebase_core.dart';
import 'package:firebase_database/firebase_database.dart';
import 'package:flutter/material.dart';

void main() async {
  WidgetsFlutterBinding.ensureInitialized();
  await Firebase.initializeApp();
  runApp(MyApp());
}

class MyApp extends StatelessWidget {
  @override
  Widget build(BuildContext context) {
    return MaterialApp(
      debugShowCheckedModeBanner: false,
      home: TemperatureHumidityDisplay(),
    );
  }
}

class TemperatureHumidityDisplay extends StatefulWidget {
  @override
  _TemperatureHumidityDisplayState createState() =>
      _TemperatureHumidityDisplayState();
}

class _TemperatureHumidityDisplayState
    extends State<TemperatureHumidityDisplay> {
  final databaseReference = FirebaseDatabase.instance.reference();

  double Temperature = 0.0;
  double Humidity = 0.0;

  @override
  void initState() {
    super.initState();
    databaseReference.child('Temperature').onValue.listen((DatabaseEvent event) {
      setState(() {
        Temperature = event.snapshot.value as double;
      });
    });
    databaseReference.child('Humidity').onValue.listen((DatabaseEvent event) {
      setState(() {
        Humidity = event.snapshot.value as double;
      });
    });
  }

  @override
  Widget build(BuildContext context) {
    return Scaffold(
      appBar: AppBar(
        title: Text('Temperature & Humidity'),
      ),
      body: Center(
        child: Column(
          mainAxisAlignment: MainAxisAlignment.center,
          children: [
            Text(
              'Temperature: $Temperature',
              style: TextStyle(fontSize: 24.0),
            ),
            SizedBox(height: 20.0),
            Text(
              'Humidity: $Humidity',
              style: TextStyle(fontSize: 24.0),
            ),
          ],
        ),
      ),
    );
  }
}
