import 'package:flutter/material.dart';

class Result extends StatelessWidget {
  final int resultScore;
  final VoidCallback resetHandler;

  Result(this.resultScore, this.resetHandler);

  String get resultPhrase {
    return resultScore.toString();
  }

  @override
  Widget build(BuildContext context) {
    return Center(
      child: Column(
        children: [
          Text(
            'Final Score: ' + resultPhrase,
            style: TextStyle(fontSize: 36, fontWeight: FontWeight.bold),
            textAlign: TextAlign.center,
          ),
          ElevatedButton(
            child: Text(
              'Restart Quiz?',
            ),
            style: ElevatedButton.styleFrom(
              primary: Color(0xFF29c583),
              onPrimary: Colors.white,
            ),
            onPressed: resetHandler,
          ),
          TextButton(
            child: Text('Restart Quiz?'),
            style: TextButton.styleFrom(
              primary: Color(0xFF29c583),
              textStyle: TextStyle(
                  decoration: TextDecoration.underline,
                  fontWeight: FontWeight.bold),
            ),
            onPressed: resetHandler,
          ),
          OutlinedButton(
            child: Text(
              'Restart Quiz?',
            ),
            style: OutlinedButton.styleFrom(
                primary: Color(0xFF29c583),
                side: BorderSide(color: Color(0xFF29c583))),
            onPressed: resetHandler,
          )
        ],
      ),
    );
  }
}
