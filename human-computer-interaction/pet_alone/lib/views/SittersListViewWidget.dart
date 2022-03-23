import 'package:flutter/material.dart';
import 'package:flutter_speed_dial/flutter_speed_dial.dart';
import 'package:flutter/material.dart';
import 'package:pet_alone/fakeDB.dart';
import 'package:pet_alone/partials/userCard.dart';
import 'package:pet_alone/models/User.dart';

class SittersListViewWidget extends StatefulWidget {
  const SittersListViewWidget({Key? key}) : super(key: key);

  @override
  State<StatefulWidget> createState() => _SittersListViewWidgetState();
  
}

class _SittersListViewWidgetState extends State<SittersListViewWidget> {
  var showOnlyFavourites = false;

  @override
  Widget build(BuildContext context) {
    var cards = <Widget>[];
    
    if (!showOnlyFavourites) {
      for (var i = 0; i < FakeDB.users.length; i++) {
        cards.add(UserCard(user: i));
      }
    } else {
      for (var i = 0; i < FakeDB.users.length; i++) {
        if (FakeDB.users[i].favourite == true)
          cards.add(UserCard(user: i));
      }
    }
    return Scaffold(
      appBar: AppBar(title: Text("Sitters near you"),
        actions: [
          Padding(
            padding: EdgeInsets.all(8.0),
            child: Icon(Icons.search),
          )
        ],
      ),
      body: ListView(
        padding: const EdgeInsets.all(8),
        children: cards,
      ),
      floatingActionButton: SpeedDial(
        child: Icon(Icons.filter_alt),
        children: [
          SpeedDialChild(
            label: 'Distance',
            child: Icon(Icons.directions_walk),
            onTap: () => setState(() {  FakeDB.users.sort((a, b) => a.distance.compareTo(b.distance)); })
          ),
          SpeedDialChild(
            label: 'Rating',
            child: Icon(Icons.star),
            onTap: () => setState(() {  FakeDB.users.sort((a, b) => b.rating.compareTo(a.rating)); })
          ),
          SpeedDialChild(
            label: 'Number of Reviews',
            child: Icon(Icons.reviews),
            onTap: () => setState(() {  FakeDB.users.sort((a, b) => b.numOfReviews.compareTo(a.numOfReviews)); })
          ),
          SpeedDialChild(
            label: 'Favourites',
            child: Icon(Icons.favorite),
            onTap: () => setState(() {  FakeDB.users.sort((a, b) => b.favourite && !a.favourite ? 1 : -1); })
          )
        ],
      ),
    );
  }
}