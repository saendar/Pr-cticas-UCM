//Credits to Akshaya Niraula and Sujay Phadke (electronicsguy) and Varul Jain for all their work,
//this code is a mix of theirs, Kiono 2019
function doGet(e) { 
  Logger.log( JSON.stringify(e) );  // view parameters
  var result = 'Ok'; // assume success
  if (e.parameter == 'undefined') 
   {
    result = 'No Parameters';
   }
  else {
    var sheet_id = '1jTWjASB6MsK5vJMhU0bBoJy8_Vqje_kH4lxWZHC0zV8';       // Spreadsheet ID
    var sheet = SpreadsheetApp.openById(sheet_id).getActiveSheet();
    var newRow = sheet.getLastRow() + 1;                        
    var rowData = [];
    rowData[0] = new Date();                                            // Timestamp in column A	
    for (var param in e.parameter) {
      Logger.log('In for loop, param=' + param);
      var value = stripQuotes(e.parameter[param]);
      Logger.log(param + ':' + e.parameter[param]);
      switch (param) {
        case 'parameter01': //Parameter
          rowData[1] = value; //Value in column B
          result = 'Written on column B';
          break;
        case 'parameter02': //Parameter
          rowData[2] = value; //Value in column B
          result = 'Written on column C';
          break;
        case 'parameter03': //Parameter
          rowData[3] = value; //Value in column C
          result += ' ,Written on column D';
          break;  
        default:
         result = "unsupported parameter";
      }
    }
    Logger.log(JSON.stringify(rowData));
    // Write new row below
    var newRange = sheet.getRange(newRow, 1, 1, rowData.length);
    newRange.setValues([rowData]);
  }
  // Return result of operation
  return ContentService.createTextOutput(result);
}
/**
* Remove leading and trailing single or double quotes
*/
function stripQuotes( value ) {
  return value.replace(/^["']|['"]$/g, "");
}
