import 'package:flutter/material.dart';
import 'package:pet_alone/models/User.dart';
import 'package:pet_alone/models/Review.dart';
import 'package:pet_alone/fakeDB.dart';
import 'package:flutter_rating_bar/flutter_rating_bar.dart';
import 'package:pet_alone/partials/datePicker.dart';

class ProfileWidget extends StatefulWidget {
  var userData;

  ProfileWidget({Key? key, required User user}) : super(key: key) {
    this.userData = user;
  }

  @override
  State<StatefulWidget> createState() =>
      _ProfileWidgetState(user: userData, reviews: FakeDB.reviews);
}

class _ProfileWidgetState extends State<ProfileWidget> {
  var userData, reviews;

  _ProfileWidgetState({required User user, required List<Review> reviews}) {
    this.userData = user;
    this.reviews = reviews;
  }

  @override
  Widget build(BuildContext context) {
    return Scaffold(
        appBar: AppBar(
          title: Text('@' + userData.username),
        ),
        body: Container(
          height: double.infinity,
          child: SingleChildScrollView(
            child: Column(
              crossAxisAlignment: CrossAxisAlignment.center,
              children: [
                Card(
                    elevation: 8,
                    margin: EdgeInsets.symmetric(vertical: 0, horizontal: 10),
                    child: Padding(
                      padding: EdgeInsets.all(15),
                      child: Column(
                        crossAxisAlignment: CrossAxisAlignment.center,
                        children: [
                          Row(
                            mainAxisAlignment: MainAxisAlignment.center,
                            children: [
                              Container(
                                  margin: EdgeInsets.all(16.0),
                                  width: 190.0,
                                  height: 190.0,
                                  decoration: BoxDecoration(
                                      boxShadow: [
                                        BoxShadow(
                                          color: Colors.grey.withOpacity(0.8),
                                          spreadRadius: 2,
                                          blurRadius: 5,
                                          offset: const Offset(0, 7),
                                        )
                                      ],
                                      shape: BoxShape.circle,
                                      image: DecorationImage(
                                          fit: BoxFit.fill,
                                          image: AssetImage(userData.picture))))
                            ],
                          ),
                          Center(
                              child: Text(
                            userData.firstName,
                            style: TextStyle(fontSize: 28),
                          )),
                          RatingBar(
                              initialRating: userData.rating.toDouble(),
                              direction: Axis.horizontal,
                              allowHalfRating: true,
                              itemCount: 5,
                              ratingWidget: RatingWidget(
                                  full: const Icon(Icons.star,
                                      color: Colors.blue),
                                  half: const Icon(
                                    Icons.star_half,
                                    color: Colors.blue,
                                  ),
                                  empty: const Icon(
                                    Icons.star_outline,
                                    color: Colors.blue,
                                  )),
                              onRatingUpdate: (rating) {
                                final snackbar = SnackBar(
                                    duration: Duration(seconds: 2),
                                    content: Text(
                                        'Your rating for ${userData.firstName} has been updated to ${rating} stars!'));
                                ScaffoldMessenger.of(context)
                                    .showSnackBar(snackbar);
                              }),
                          // RatingBar.builder(
                          //   initialRating: userData.rating,
                          //   minRating: 1,
                          //   direction: Axis.horizontal,
                          //   allowHalfRating: true,
                          //   itemCount: 5,
                          //   itemPadding:
                          //       EdgeInsets.symmetric(horizontal: 4.0),
                          //   itemBuilder: (context, _) => Icon(
                          //     Icons.star,
                          //     color: Colors.blue,
                          //   ),
                          // onRatingUpdate: (rating) {
                          //   final snackbar = SnackBar(
                          //       duration: Duration(seconds: 2),
                          //       content: Text(
                          //           'Your rating for ${userData.firstName} has been updated to ${rating} stars!'));
                          //   ScaffoldMessenger.of(context)
                          //       .showSnackBar(snackbar);
                          // },
                          // ),
                          SizedBox(height: 12),
                          Chip(
                              label: Text(userData.location),
                              shape: StadiumBorder(
                                  side: BorderSide(color: Colors.grey)),
                              padding: EdgeInsets.all(8),
                              avatar: Icon(Icons.location_on, size: 18)),
                          SizedBox(height: 12),
                          Row(
                              mainAxisAlignment: MainAxisAlignment.spaceEvenly,
                              children: userData.pettingServices
                                  .map<Widget>((p) => Chip(
                                      label: Text(p),
                                      padding: EdgeInsets.all(8),
                                      shape: StadiumBorder(
                                          side: BorderSide(color: Colors.grey)),
                                      avatar: Icon(Icons.pets, size: 18)))
                                  .toList())
                        ],
                      ),
                    )),
                Column(
                    crossAxisAlignment: CrossAxisAlignment.center,
                    children: [
                      SizedBox(height: 48),
                      Container(
                        margin:
                            EdgeInsets.symmetric(vertical: 0, horizontal: 20),
                        alignment: Alignment.topLeft,
                        child: Column(
                          crossAxisAlignment: CrossAxisAlignment.start,
                          children: [
                            Text('Something about me',
                                style: TextStyle(fontSize: 25)),
                            Text(userData.about),
                            SizedBox(height: 48),
                            Text('Check out my pets',
                                style: TextStyle(fontSize: 25)),
                            ListView(
                              shrinkWrap: true,
                              children: userData.pets
                                  .map<Widget>((p) => ListTile(
                                      title: Text(p.name,
                                          style: TextStyle(fontSize: 25)),
                                      leading: CircleAvatar(
                                          backgroundImage:
                                              AssetImage(p.petPhoto))))
                                  .toList(),
                            ),
                          ],
                        ),
                      ),
                      SizedBox(height: 30),
                      Card(
                          elevation: 8,
                          margin:
                              EdgeInsets.symmetric(vertical: 0, horizontal: 20),
                          child: Padding(
                            padding: EdgeInsets.all(15),
                            child: Column(
                              crossAxisAlignment: CrossAxisAlignment.start,
                              children: [
                                Text('Availability',
                                    style: TextStyle(fontSize: 25)),
                                Text(
                                    'I am available for your little friend from ${userData.availableFrom} until ${userData.availableTo}. Hit me up if you are interested or notify me via chatting!'),
                                SizedBox(height: 30),
                                SizedBox(
                                  width: double.infinity,
                                  child: ElevatedButton.icon(
                                    onPressed: () async {
                                      DatePicker dp = new DatePicker(
                                          df: userData.availableFrom,
                                          dt: userData.availableTo);
                                      dp.pickDateRange(context);
                                    },
                                    style: ButtonStyle(
                                      backgroundColor: MaterialStateProperty
                                          .resolveWith<Color>(
                                        (Set<MaterialState> states) {
                                          if (states.contains(
                                              MaterialState.pressed)) {
                                            return Colors.green;
                                          }
                                          return Colors
                                              .green; // Use the component's default.
                                        },
                                      ),
                                    ),
                                    icon: Icon(Icons.add, size: 18),
                                    label: Text('NOTIFY SITTER'),
                                  ),
                                )
                              ],
                            ),
                          )),
                      SizedBox(height: 30),
                      Container(
                        padding: EdgeInsets.all(0),
                        margin:
                            EdgeInsets.symmetric(vertical: 0, horizontal: 20),
                        child: Column(
                          crossAxisAlignment: CrossAxisAlignment.start,
                          mainAxisAlignment: MainAxisAlignment.start,
                          children: [
                            Text('Reviews', style: TextStyle(fontSize: 25)),
                            ListView(
                                shrinkWrap: true,
                                children: reviews
                                    .map<Widget>((r) => ListTile(
                                          leading: CircleAvatar(
                                              backgroundImage:
                                                  AssetImage(r.picture)),
                                          title: Row(
                                            mainAxisAlignment:
                                                MainAxisAlignment.spaceBetween,
                                            children: [
                                              Text(r.username),
                                              RatingBar(
                                                  itemSize: 18,
                                                  initialRating: r.rating.toDouble(),
                                                  direction: Axis.horizontal,
                                                  allowHalfRating: true,
                                                  itemCount: 5,
                                                  ratingWidget: RatingWidget(
                                                      full: const Icon(
                                                          Icons.star,
                                                          color: Colors.blue),
                                                      half: const Icon(
                                                        Icons.star_half,
                                                        color: Colors.blue,
                                                      ),
                                                      empty: const Icon(
                                                        Icons.star_outline,
                                                        color: Colors.blue,
                                                      )),
                                                  onRatingUpdate: (rating) {})
                                            ],
                                          ),
                                          subtitle: Text(r.comment),
                                          isThreeLine: true,
                                          trailing: Row(
                                            mainAxisSize: MainAxisSize.min,
                                            children: <Widget>[],
                                          ),
                                        ))
                                    .toList())
                          ],
                        ),
                      )
                    ])
              ],
            ),
          ),
        ));
  }
}
