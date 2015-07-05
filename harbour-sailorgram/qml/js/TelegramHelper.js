.pragma library

.import harbour.sailorgram.TelegramCalendar 1.0 as TelegramCalendar
.import "TelegramConstants.js" as TelegramConstants

function userName(user)
{
    return ((user.username.length > 0) ? user.username : (user.firstName + " " + user.lastName));
}

function phoneNumber(user)
{
    return completePhoneNumber(user.phone);
}

function userStatus(user)
{
    switch(user.status.classType)
    {
        case TelegramConstants.typeUserStatusRecently:
            return qsTr("Recently");

        case TelegramConstants.typeUserStatusLastMonth:
            return qsTr("Last Month");

        case TelegramConstants.typeUserStatusLastWeek:
            return qsTr("Last Week");

        case TelegramConstants.typeUserStatusOnline:
            return qsTr("Online");

        case TelegramConstants.typeUserStatusOffline:
            return qsTr("Last Seen at %1").arg(TelegramCalendar.TelegramCalendar.timeToString(user.status.wasOnline));

        default:
            break;
    }

    return qsTr("Unknown");
}

function isChat(dialog)
{
    if(!dialog)
        return false;

    return dialog.peer.classType === TelegramConstants.typePeerChat;
}

function peerId(peer)
{
    if(peer.classType === TelegramConstants.typePeerChat)
        return peer.chatId;

    return peer.userId;
}

function messageContent(message)
{
    if(message.media)
    {
        switch(message.media.classType)
        {
            case TelegramConstants.typeMessageMediaDocument:
                return qsTr("Document");

            case TelegramConstants.typeMessageMediaContact:
                return qsTr("Contact");

            case TelegramConstants.typeMessageMediaVideo:
                return qsTr("Video");

            case TelegramConstants.typeMessageMediaUnsupported:
                return qsTr("Unsupported");

            case TelegramConstants.typeMessageMediaAudio:
                return qsTr("Audio");

            case TelegramConstants.typeMessageMediaPhoto:
                return qsTr("Photo");

            case TelegramConstants.typeMessageMediaGeo:
                return qsTr("Geo");

            default:
                break;
        }
    }

    return message.message;
}

function formatBytes(bytes, decimals)
{
   if(bytes === 0)
       return "0 Byte";

   var k = 1024;
   var dm = decimals + 1 || 3;
   var sizes = ["Bytes", "KiB", "MiB", "GiB", "TiB", "PiB", "EiB", "ZiB", "YiB"];
   var i = Math.floor(Math.log(bytes) / Math.log(k));

   return (bytes / Math.pow(k, i)).toPrecision(dm) + " " + sizes[i];
}

function completePhoneNumber(phonenumber)
{
    if(phonenumber[0] !== '+')
        return "+" + phonenumber;

    return phonenumber;
}

function isTelegramUser(user) // https://core.telegram.org/constructor/updateServiceNotification
{
    return user.id === 777000;
}
