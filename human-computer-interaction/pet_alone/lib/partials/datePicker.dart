import 'package:flutter/cupertino.dart';
import 'package:flutter/material.dart';

class DatePicker {
  var dateFrom, dateTo; 

  DatePicker({required String df, required String dt}) {
    dateFrom = df;
    dateTo = dt;
  }

  Future pickDateRange(context) async {
    var dateRange = DateTimeRange(start: DateTime.parse(dateFrom), end: DateTime.parse(dateTo));  

    DateTimeRange? newDateRange = await showDateRangePicker(
        context: context,
        initialDateRange: dateRange
        firstDate: dateRange.start,
        lastDate: dateRange.end);

    if (newDateRange == null) return;

    showDialog(
    context: context,
    builder: (context) => Center(
      child: AlertDialog(
        title: const Text('Reservation successful'),
        content: SingleChildScrollView(
          child: ListBody(
            children: const <Widget>[
              Icon(Icons.check_circle_outline_sharp, size: 70, color: Colors.blue),
              Text('The sitter will be notified about your reservation and will contact you for more information!')
            ],
          ),
        ),
        actions: <Widget>[
          TextButton(
            child: const Text('GOT IT'),
            onPressed: () {
              Navigator.of(context).pop();
            },
          ),
        ],
      ),
    )
  );
  }
}