// Converted from StudentResult.java to JavaScript
// Same logic: Scanner -> prompt(), System.out -> document.write() / alert()

function runStudentResult() {
    let n = parseInt(prompt("Enter number of subjects:"));
    let marks = [];
    let total = 0;

    for (let i = 0; i < n; i++) {
        let m = parseInt(prompt("Enter marks for subject " + (i + 1) + ":"));
        marks.push(m);
        total += m;
    }

    let percentage = total / n;
    let grade;

    if (percentage >= 90) grade = "A+";
    else if (percentage >= 75) grade = "A";
    else if (percentage >= 60) grade = "B";
    else if (percentage >= 40) grade = "C";
    else grade = "Fail";

    document.getElementById("output").innerHTML =
        "<p><b>Total Marks:</b> " + total + "</p>" +
        "<p><b>Percentage:</b> " + percentage.toFixed(2) + "%</p>" +
        "<p><b>Grade:</b> " + grade + "</p>";
}
