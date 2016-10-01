    //********************************************************************************//
    //* Name : Julian Philip Hernandez                                                                      *//
    //* zenit login : int222_161c10                                                     *//
    //********************************************************************************//
    //********************************************************************************//
    //*   Do not modify any statements in detailPaymentCalculation function          *//
    //********************************************************************************//

function detailPaymentCalculation(mortAmount,mortDownPayment,mortRate,mortAmortization)
{

    //********************************************************************************//
    //*   This function calculates the monthly payment based on the following:       *//
    //*                                                                              *//
    //*               M = P [ i(1 + i)n ] / [ (1 +  i)n - 1]                         *//
    //*                                                                              *//
    //*   Note: This function also updates the payment amount on the form            *//
    //********************************************************************************//
     var paymentError = "";
     var v = mortAmount * 1;
     var d = mortDownPayment * 1;
     var i = mortRate * 1;
     var y = mortAmortization * 1;
     var a = v - d;
         i = i/100/12;
         n = y * 12;
     var f = Math.pow((1+i),n);

     var p = (a * ((i*f)/(f-1))).toFixed(2);

     if (p=="NaN" || p=="Infinity") {
         document.forms[0].payment.value = "";
     }
     else {
           document.forms[0].payment.value = p;
     }

} // End of detailPaymentCalculation function


function calculatePayment()
{

    //********************************************************************************//
    //*   You will need to call the functions that validate the following:           *//
    //********************************************************************************//
    //*        (1)              (2)              (3)             (4)                 *//
    //********************************************************************************//
    //*   Property value  -  Down payment  -  Interest rate -  Amortization          *//
    //********************************************************************************//
    //*   If there are no errors, then call                                          *//
    //*                                                                              *//
    //*      detailPaymentCalculation(...., ......, ......, ......);                 *//
    //*                                                                              *//
    //*   and make sure to pass the four values in the order shown above.            *//
    //*                                                                              *//
    //********************************************************************************//
    //*   If there are errors, present the client the following message in the       *//
    //*   reserved area on the form:                                                 *//
    //*                                                                              *//
    //*   Please complete the form first and then click on Calculate Monthly Payment *//
    //*                                                                              *//
    //********************************************************************************//

var errMessages = "";
//call functions that validate propValue, downPay, intRate, and amortization, and stream errMessages

errMessages = propValue_validation(errMessages);
errMessages = downPay_validation(errMessages);
errMessages = intRate_validation(errMessages);
errMessages = amortization_validation(errMessages);

if (errMessages !== "")
{
  document.getElementById('errors').innerHTML = "<p> Please complete the form first and then click on Calculate Monthly Payment</p>";
}
else
{
  detailPaymentCalculation(document.mortgage.propValue.value,document.mortgage.downPay.value,
                           document.mortgage.intRate.value, document.mortgage.amortization.value);
}

} // End of calculatePayment function



function formValidation()
{

    //***************************************************************************************//
    //*                                                                                     *//
    //* This function calls the different functions to validate all required fields         *//
    //*                                                                                     *//
    //* Once you have called and validated all field, determine if any error(s)             *//
    //*  have been encountered                                                              *//
    //*                                                                                     *//
    //* If any of the required fields are in error:                                         *//
    //*                                                                                     *//
    //*    present the client with a list of all the errors in reserved area                *//
    //*         on the form and                                                             *//
    //*          don't submit the form to the CGI program in order to allow the             *//
    //*          client to correct the fields in error                                      *//
    //*                                                                                     *//
    //*    Error errMessages should be meaningful and reflect the exact error condition.    *//
    //*                                                                                     *//
    //*    Make sure to return false                                                        *//
    //*                                                                                     *//
    //* Otherwise (if there are no errors)                                                  *//
    //*                                                                                     *//
    //*    Recalculate the monthly payment by calling                                       *//
    //*      detailPaymentCalculation(mortAmount,mortDownPayment,mortRate,mortAmortization) *//
    //*                                                                                     *//
    //*    Change the 1st. character in the field called client to upper case               *//
    //*                                                                                     *//
    //*    Change the initial value in the field called jsActive from N to Y                *//
    //*                                                                                     *//
    //*    Make sure to return true in order for the form to be submitted to the CGI        *//
    //*                                                                                     *//
    //***************************************************************************************//
var errMessages = "";
//call and validate all fields and check for errors
errMessages = amortization_validation(errMessages);
errMessages = intRate_validation(errMessages);
errMessages = mortYear_validation(errMessages);
errMessages = mortMonth_validation(errMessages);
errMessages = client_Validation(errMessages);
errMessages = userId_validation(errMessages);
errMessages = propValue_validation(errMessages);
errMessages = downPay_validation(errMessages);
errMessages = propLocation_validation(errMessages);
errMessages = income_validation(errMessages);
errMessages = propDetails_validation(errMessages);

if (errMessages !== "")
{
  showErrors(errMessages);
  return false;
}
else
{
  detailPaymentCalculation(document.mortgage.propValue.value,document.mortgage.downPay.value,
                           document.mortgage.intRate.value, document.mortgage.amortization.value);
  clearShowErrors();
  clientFirstCharToUpper();
  getElementById('jsActive').value = "Y";
  return true;
}

} // End of completeFormValidation

function showErrors(errMessages)
{
  document.getElementById('errors').innerHTML = errMessages;
}

function clearShowErrors()
{
  document.getElementById('errors').innerHTML = "";
}

function clientFirstCharToUpper()
{
  var clientId = document.mortgage.client.value;
  clientId = clientId.substr(0,1).toUpperCase() + clientId.substr(1,clientId.length - 1);
  document.mortgage.client.value = clientId;
}

function client_Validation(errMessages)
{
  var client = document.getElementById('client').value;
  client = client.toUpperCase();
  var firstThree = client.substr(0,3);
  var nonAlpha = 0;
  var numOfApos = 0;
  var foundNonChar = 0;
  if (client.length === 0)
  {
    errMessages += "<mark>Client Name</mark> field is empty!<br><br>";
  }
  else if (client.indexOf(' ') !== -1)
  {
    errMessages += "You cannot have blanks in <mark>Client Name</mark>!<br><br>";
  }
  else if (client.substr(0,1) === "'" || client.substr(client.length-1,1) ==="'")
  {
    errMessages += "An apostrophe at the beginning or at the end of the <mark>Client Name</mark> is not valid!<br><br>";
  }
  else
  {
     for (var k in firstThree)
    {
      if (!(firstThree.charCodeAt(k) > 64 && firstThree.charCodeAt(k) < 91) || firstThree.length !== 3)
      {
        foundNonChar++;
      }
    }
    if (foundNonChar !== 0)
    {
        errMessages += "<mark>Client Name</mark> must have at least 3 alphabetic characters (A-Z) at the beginning of the field<br><br>";
    }
    else
    {
      for (var i in client)
      {
        if (!((client.charCodeAt(i) > 64) && (client.charCodeAt(i) < 91) && client[i] !=="'"))
        {
          nonAlpha++;
        }
        if (client.charCodeAt(i) === "'")
        {
          numOfApos++;
        }
      }
      if (numOfApos >= 2)
      {
         errMessages += "<mark>Client Name/<mark> can only have one apostrophe!<br><br>";
      }
      else if (nonAlpha > 0 )
      {
        errMessages += "<mark>Client Name</mark> cannot contain non-alphabetic charaters!<br><br>";
      }
    }
  }
  return errMessages;
}

function userId_validation(errMessages)
{
  var userId = document.getElementById('userId').value;
  userId = userId.trim();
  var firstFour = userId.substr(0,4);
  var lastFive = userId.substr(6,5);
  var ruleBroken = false;
  // Rule #1
  if (userId.length === 0)
  {
    errMessages += "<mark>Client ID</mark> cannot be empty!<br><br>";
  }
  else if (userId.length > 10 || userId.length < 1)
  {
    errMessages += "Please enter all 9 digits of your <mark>Client ID</mark>!<br><br>";
    ruleBroken = true;
  }
  else if (userId.substr(4,1) !== "-")
  {
    errMessages += "Invalid <mark>Client ID</mark>: there should be a hyphen after the 4th digit!<br><br>";
    ruleBroken = true;
  }
  else if (isNaN(firstFour) === true)
  {
    errMessages += "The first 4 characters of <mark>Client ID</mark> must be numeric digits!<br><br>";
    ruleBroken = true;
  }
  else if (isNaN(lastFive) === true)
  {
    errMessages += "<mark>Invalid Client ID</mark>: the last 5 characters after the hyphen must be numeric digits!<br><br>";
    ruleBroken = true;
  }
  else if (ruleBroken !== true) // Executes only if rules 1-4 are not broken
  {
    var firstFourDigits = userId.substr(0,4).split("");
    var sumOfFourDigits = 0;
    for (var i in firstFourDigits)
    {
      sumOfFourDigits += +firstFourDigits[i];
    }
    var lastFiveDigits = userId.substr(5,5).split("");
    var sumOfFiveDigits = 0;
    for (var j in lastFiveDigits)
    {
      sumOfFiveDigits += +lastFiveDigits[j];
    }
    // Rule #5
    if (sumOfFiveDigits < 1 || sumOfFourDigits < 1)
    {
      errMessages += "Invalid <mark>Client ID</Mark>: the first four digits and last 5 digits must be greater than 0!<br><br>";
    }
    // Rule #6
    else if ((sumOfFourDigits * 2 + 2) !== sumOfFiveDigits)
    {
      errMessages += "Invalid <mark>Client ID</mark>: The sum of the numbers to the right of the hyphen must be double plus two the sum of the numbers on the left of the hyphen!<br><br>";
    }
  }
  return errMessages;
}

function propValue_validation(errMessages)
{
  var propValue = document.getElementById('propValue').value;
  var downPay = document.getElementById('downPay').value;
  if (propValue.length === 0)
  {
    errMessages += "Please enter <mark>Property Value</mark>!<br><br>";
  }
  else if (propValue < 65000)
  {
    errMessages += "<mark>Property value</mark> must be at least $65,000!<br><br>";
  }
  else if (propValue % 1 !== 0 || propValue < 1 || isNaN(propValue) || propValue.indexOf(' ') !== -1)
  {
    errMessages += "<mark>Property value</mark> must be a positive whole number!<br><br>";
  }
  else if (propValue < downPay + 65000)
  {
    errMessages += "<mark>Property value</mark> must be at least $65,000 more than the down payment!<br><br>";
  }
  return errMessages;
}

function downPay_validation(errMessages)
{
  var downPay = document.getElementById('downPay').value;
  var propValue = document.getElementById('propValue').value;
  if (downPay.length === 0)
  {
    errMessages += "Please enter <mark>Down Payment</mark>!<br><br>";
  }
  else if (downPay % 1 !== 0 || downPay < 1 || isNaN(downPay) || downPay.indexOf(' ') !== -1)
  {
    errMessages += "<mark>Down Payment</mark> must be a postitive whole number!<br><br>";
  }
  else if (propValue * 0.20 > downPay)
  {
    errMessages += "<mark>Down Payment</mark> must be at least 20% of the value of the property!<br><br>";
  }
  return errMessages;
}

function income_validation(errMessages)
{
  var selectedOptions = document.mortgage.income.selectedIndex;
  if (selectedOptions === -1)
  {
    errMessages += "Please select your <mark>Income</mark> range!<br><br>";
  }
  return errMessages;
}


function propLocation_validation(errMessages)
{
  var selectedOptions = document.mortgage.propLocation.selectedIndex;
  if (selectedOptions === -1)
  {
    errMessages += "Please choose a <mark>Location</mark>!<br><br>";
  }
  return errMessages;
}

function propDetails_validation(errMessages)
{
  var noOfRadio = document.mortgage.propDetails.length;
  var checked = false;
  for (var i = 0; i < noOfRadio; i++)
  {
    if (document.mortgage.propDetails[i].checked === true)
    {
      checked = true;
    }
  }
  if (checked === false)
  {
    errMessages += "Please choose a <mark>Property Type</mark>!<br><br>";
  }
  return errMessages;
}

function mortYear_validation(errMessages)
{
  var mortYear = document.getElementById('mortYear').value;
  var myDate = new Date();
  var myYear = myDate.getFullYear();
  if (mortYear.length === 0)
  {
    errMessages += "Please enter <mark>Year</mark> under Mortgage details!<br><br>";
  }
  else if (isNaN(mortYear))
  {
    errMessages += "<mark>Year</mark> must be numeric!<br><br>";
  }
  else if (+mortYear !== +myYear  && +mortYear !== +myYear + 1)
  {
    errMessages += "<mark>Year</mark> must be this current year or the next!<br><br>";
  }
  return errMessages;
}

function mortMonth_validation(errMessages)
{
  var mortMonth = document.getElementById('mortMonth').value;
  var myDate = new Date();
  var myMonth = myDate.getMonth();
  var nextMonth = +myMonth + 1;
  if (mortMonth.length === 0)
  {
    errMessages += "Please fill-out <mark>Month</mark> under Mortgage details!<br><br>";
  }
  else if (isNaN(mortMonth))
  {
    errMessages += "<mark>Month</mark> must be numeric!<br><br>";
  }
  else if (mortMonth < 1 || mortMonth > 12)
  {
    errMessages += "<mark>Month</mark> can only be from 1-12!<br><br>";
  }
  else if (+mortMonth !== +nextMonth && +mortMonth !== +myMonth )
  {
    errMessages += "<mark>Month</mark> must be this current month or the next!<br><br>";
  }
  return errMessages;
}

function intRate_validation(errMessages)
{
  var intRate = document.getElementById('intRate').value;
  if (intRate.length === 0)
  {
    errMessages += "Please fill-out <mark>Interest Rate</mark> under Mortgage details!<br><br>";
  }
  else if(isNaN(intRate))
  {
    errMessages += "<mark>Interest Rate</mark> must be numeric!<br><br>";
  }
  else if(intRate < 3 || intRate > 16)
  {
    errMessages += "Allowable values for <mark>Interest Rate</mark>: 3-16<br><br>";
  }
  return errMessages;
}

function amortization_validation(errMessages)
{
  var amortization = document.getElementById('amortization').value;
  if (amortization.length === 0)
  {
    errMessages += "Please enter <mark>Amortization</mark> under Mortgage details!<br><br>";
  }
  else if(isNaN(amortization))
  {
    errMessages += "<mark>Amortization</mark> values be numeric!<br><br>";
  }
  else if(amortization < 5 || amortization > 20)
  {
    errMessages += "Allowable values for <mark>Amortization</mark>: 5-20<br><br>";
  }
  return errMessages;
}
