// Official IIEST Shibpur Grading Scale
function getGradePoint(marks) {
    if (marks >= 90) return { letter: "A+", point: 10, perf: "Excellent" };
    if (marks >= 80) return { letter: "A", point: 9, perf: "Very Good" };
    if (marks >= 70) return { letter: "B", point: 8, perf: "Good" };
    if (marks >= 60) return { letter: "C", point: 7, perf: "Fair" };
    if (marks >= 50) return { letter: "D", point: 6, perf: "Average" };
    if (marks >= 40) return { letter: "P", point: 5, perf: "Pass" };
    return { letter: "F", point: 0, perf: "Fail" };
}

function calculateSGPA() {
    const numSubjects = 5;
    const errorMsg = document.getElementById("errorMsg");
    const resultDiv = document.getElementById("result");

    errorMsg.textContent = "";
    resultDiv.style.display = "none";

    let subjects = [];
    let totalMarks = 0;
    let totalCredits = 0;
    let totalGradePointsEarned = 0;
    let hasFail = false;

    for (let i = 0; i < numSubjects; i++) {
        const nameField = document.getElementById("sub" + i);
        const credField = document.getElementById("cred" + i);
        const marksField = document.getElementById("marks" + i);

        const name = nameField.value.trim() || ("Subject " + (i + 1));
        const credValue = credField.value.trim();
        const marksValue = marksField.value.trim();

        // Error checking for empty fields
        if (marksValue === "" || credValue === "") {
            errorMsg.textContent = "Please enter both credits and marks for all subjects.";
            return;
        }

        const credits = Number(credValue);
        const marks = Number(marksValue);

        // Validation: Credits must be at least 1
        if (isNaN(credits) || credits < 1) {
            errorMsg.textContent = "Credits for \"" + name + "\" must be a positive number (at least 1).";
            return;
        }

        if (isNaN(marks) || marks < 0 || marks > 100) {
            errorMsg.textContent = "Marks for \"" + name + "\" must be between 0 and 100.";
            return;
        }

        const grade = getGradePoint(marks);
        if (grade.letter === "F") hasFail = true;

        const creditPointsEarned = credits * grade.point;

        totalMarks += marks;
        totalCredits += credits;
        totalGradePointsEarned += creditPointsEarned;

        subjects.push({
            name: name,
            credits: credits,
            marks: marks,
            letter: grade.letter,
            point: grade.point,
            pointsEarned: creditPointsEarned
        });
    }

    const sgpa = totalGradePointsEarned / totalCredits;
    const percentage = (totalMarks / (numSubjects * 100)) * 100;
    const finalStatus = hasFail ? "FAIL" : "PASS";

    // Build IIEST style breakdown table
    let breakdown = "<table style='margin:15px auto; width:100%; border-collapse:collapse; text-align:center;'>";
    breakdown += "<tr>" +
                 "<th style='padding:6px;'>Subject</th>" +
                 "<th style='padding:6px;'>Credits</th>" +
                 "<th style='padding:6px;'>Marks</th>" +
                 "<th style='padding:6px;'>Grade</th>" +
                 "<th style='padding:6px;'>Points Earned</th>" +
                 "</tr>";

    subjects.forEach(function (s) {
        breakdown += "<tr>" +
                     "<td style='padding:6px; text-align:left;'>" + s.name + "</td>" +
                     "<td style='padding:6px;'>" + s.credits + "</td>" +
                     "<td style='padding:6px;'>" + s.marks + "</td>" +
                     "<td style='padding:6px;'>" + s.letter + "</td>" +
                     "<td style='padding:6px;'>" + s.pointsEarned + "</td>" +
                     "</tr>";
    });
    breakdown += "</table>";

    resultDiv.innerHTML =
        "<p>Total Credits: " + totalCredits + "</p>" +
        "<p>Total Points Earned: " + totalGradePointsEarned + "</p>" +
        "<p>Overall Average Marks: " + percentage.toFixed(2) + "%</p>" +
        "<p style='font-size:22px; margin:10px 0;'>SGPA: " + sgpa.toFixed(2) + "</p>" +
        "<p>Result: " + finalStatus + (sgpa >= 8.5 && !hasFail ? " (Distinction)" : "") + "</p>" +
        breakdown;

    // Dynamic styling based on result
    resultDiv.className = hasFail ? "fail-result" : "pass-result";
    resultDiv.style.display = "block";

    document.body.style.backgroundColor = hasFail ? "#fbe4e6" : "#e6f7ea";
}