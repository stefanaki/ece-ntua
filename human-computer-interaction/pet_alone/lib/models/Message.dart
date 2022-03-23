import 'package:pet_alone/models/User.dart';
import 'package:pet_alone/fakeDB.dart';

class Message {
  final User sender;
  final String time; // Would usually be type DateTime or Firebase Timestamp in production apps
  final String text;
  final bool unread;

  Message({
    required this.sender,
    required this.time,
    required this.text,
    required this.unread,
  });
}

// EXAMPLE CHATS ON HOME SCREEN
List<Message> chats = [
  Message(
    sender: FakeDB.users[0],
    time: '5:30 PM',
    text: 'geia sou file mou! ti kaneis?',
    unread: true,
  ),
  Message(
    sender: FakeDB.users[1],
    time: '4:30 PM',
    text: 'mporeis na filokseniseis ton tsosmi?',
    unread: true,
  ),
  Message(
    sender: FakeDB.users[3],
    time: '2:30 PM',
    text: 'send location',
    unread: true,
  ),
  Message(
    sender: FakeDB.users[4],
    time: '1:30 PM',
    text: 'na sou pw h gata kamia fora tin kanei ap to spiti min tromakseis tha gurisei',
    unread: false,
  ),
  Message(
    sender: FakeDB.users[5],
    time: '12:30 PM',
    text: 'pspspspspsps',
    unread: false,
  ),
  Message(
    sender: FakeDB.users[6],
    time: '11:30 AM',
    text: 'eisai megalos mlks agori mou',
    unread: false,
  ),
];

// EXAMPLE MESSAGES IN CHAT SCREEN
List<Message> messages = [
  Message(
    sender: FakeDB.users[2],
    time: '5:30 PM',
    text: 'ok ta leme stis 5 stin geraniou',
    unread: true,
  ),
  Message(
    sender: FakeDB.users[0],
    time: '4:30 PM',
    text: 'entaaaaaksei, thes na vrethoume stis 5?',
    unread: true,
  ),
  Message(
    sender: FakeDB.users[2],
    time: '3:45 PM',
    text: 'afou einai mia vasilisa',
    unread: true,
  ),
  Message(
    sender: FakeDB.users[0],
    time: '3:15 PM',
    text: 'ligo akrivi den einai auti?? :(',
    unread: true,
  ),
  Message(
    sender: FakeDB.users[2],
    time: '2:30 PM',
    text: 'entaksei!!!! trwei mono whiskas na to thumasai',
    unread: true,
  ),
  Message(
    sender: FakeDB.users[0],
    time: '2:30 PM',
    text: 'pame mia volta plateia kai fere mou tin mesa sto klouvaki tis',
    unread: true,
  ),
  Message(
    sender: FakeDB.users[2],
    time: '2:30 PM',
    text: 'nai se parakalw giati prepei na fugw gia ena taksidi',
    unread: true,
  ),
  Message(
    sender: FakeDB.users[0],
    time: '2:00 PM',
    text: 'geia sou!! eida oti theleis na filoksenisw tin fifi gia merikes meres',
    unread: true,
  ),
];