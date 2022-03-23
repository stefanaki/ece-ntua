// ignore_for_file: deprecated_member_use

import 'package:flutter/material.dart';
import 'package:pet_alone/fakeDB.dart';
import 'package:pet_alone/models/User.dart';
import 'package:pet_alone/views/ProfileWidget.dart';
import 'package:pet_alone/partials/datePicker.dart';
import 'package:pet_alone/views/ChatWidget.dart';

class UserCard extends StatefulWidget {
  var userIndex;

  UserCard({Key? key, required int user}) : super(key: key) {
    userIndex = user;
  }

  @override
  State<StatefulWidget> createState() => _UserCardState(user: userIndex);
}

class _UserCardState extends State<UserCard> {
  var userIndex;

  _UserCardState({required int user}) {
    userIndex = user;
  }

  @override
  Widget build(BuildContext context) {
    return Wrap(
      children: [
        Card(
            clipBehavior: Clip.antiAlias,
            child: Column(
              children: [
                ListTile(
                  leading: CircleAvatar(backgroundImage: AssetImage (FakeDB.users[userIndex].picture)),
                  title: Text(FakeDB.users[userIndex].firstName),
                  subtitle: Text(
                    FakeDB.users[userIndex].location,
                    style: TextStyle(color: Colors.black.withOpacity(0.6)),
                  ),
                ),
                Container(
                  width: MediaQuery.of(context).size.width,
                  height: 250,
                  decoration: BoxDecoration(
                    image: DecorationImage(
                      fit: BoxFit.fitWidth,
                      alignment: Alignment.topCenter,
                      image: AssetImage(FakeDB.users[userIndex].picture),
                    ),
                  ),
                ),
                Padding(
                  padding: const EdgeInsets.all(16.0),
                  child: Text(
                    FakeDB.users[userIndex].about,
                    style: TextStyle(color: Colors.black.withOpacity(0.6)),
                  ),
                ),
                Row(
                  mainAxisAlignment: MainAxisAlignment.spaceBetween,
                  children: [
                    ButtonBar(
                      alignment: MainAxisAlignment.start,
                      children: [
                        FlatButton(
                            onPressed: () {
                              Navigator.push(
                                  context,
                                  MaterialPageRoute(
                                      builder: ((context) => ProfileWidget(
                                          user: FakeDB.users[userIndex]))));
                            },
                            child: Text('VIEW PROFILE')),
                        FlatButton(
                          onPressed: () {
                            DatePicker dp = new DatePicker(
                                df: FakeDB.users[userIndex].availableFrom,
                                dt: FakeDB.users[userIndex].availableTo);
                            dp.pickDateRange(context);
                          },
                          child: Text('KEEP MY PET'),
                        ),
                      ],
                    ),
                    Expanded(
                        child: ButtonBar(
                      alignment: MainAxisAlignment.end,
                      children: [
                        FlatButton(
                          onPressed: () {
                            // Perform some action
                          },
                          child: IconButton(
                              onPressed: () {
                                Navigator.push(
                              context,
                              MaterialPageRoute(
                                builder: (_) =>
                                    ChatScreen(user: FakeDB.users[userIndex]),
                              ),
                            );

                              }, icon: Icon(Icons.message)),
                        ),
                        FlatButton(
                          onPressed: () {
                            
                          },
                          child: IconButton(
                            onPressed: () => setState(() {
                              FakeDB.users[userIndex].favourite =
                                  !FakeDB.users[userIndex].favourite;
                              final msg = FakeDB.users[userIndex].favourite
                                  ? 'Added to'
                                  : 'Removed from';
                              final snackbar = SnackBar(
                                  duration: Duration(seconds: 1),
                                  content: Text('$msg favourites!'));
                              ScaffoldMessenger.of(context)
                                  .showSnackBar(snackbar);
                            }),
                            icon: Icon(Icons.favorite),
                            color: FakeDB.users[userIndex].favourite
                                ? Colors.blue
                                : Colors.grey,
                          ),
                        ),
                      ],
                    ))
                  ],
                )
              ],
            ))
      ],
    );
  }
}
