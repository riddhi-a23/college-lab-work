function showProfile() {
    const input = document.getElementById("facultyName").value.trim().toLowerCase();
    const area = document.getElementById("profileArea");

    if (input === "") {
        area.innerHTML = "<p class='not-found'>Please enter a faculty name.</p>";
        return;
    }

    const faculty = facultyList.find(function (f) {
        return f.name.toLowerCase().includes(input);
    });

    if (!faculty) {
        area.innerHTML = "<p class='not-found'>No matching faculty found. Please check the spelling.</p>";
        return;
    }

    // Build subjects and research lists
    let subjectsHTML = "<ul>";
    faculty.subjects.forEach(function (s) {
        subjectsHTML += "<li>" + s + "</li>";
    });
    subjectsHTML += "</ul>";

    let researchHTML = "<ul>";
    faculty.research.forEach(function (r) {
        researchHTML += "<li>" + r + "</li>";
    });
    researchHTML += "</ul>";

    // Same format/template used for every faculty member
    area.innerHTML =
        "<div class='card'>" +
            "<img src='" + faculty.photo + "' alt='" + faculty.name + "'>" +
            "<h2>" + faculty.name + "</h2>" +
            "<p><b>Email:</b> " + faculty.email + "</p>" +
            "<p class='qualification'><b>Highest Qualification:</b> " + faculty.qualification + "</p>" +
            "<div class='subjects'><b>Subjects Teaching (Current Semester):</b>" + subjectsHTML + "</div>" +
            "<div class='research'><b>Research Areas:</b>" + researchHTML + "</div>" +
        "</div>";
}