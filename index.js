function showz(card) {
    var t = card.querySelector(".button-points-text");
    t.classList.toggle("button-points-faded");

    t.classList.add("button-price-text-hidden");
    t.classList.remove("button-price-text-visible");
    var s = card.parentNode.querySelector(".question-card");
    s.classList = ["question-card question-card-visible"];
}

function hide(card) {
    card.classList.remove('question-card-visible');
    card.classList.add('question-card-hidden');
}

function editname(card) {
    const parent = card.parentNode;
    const nameElem = parent.querySelector(".score-name");
    const existingName = nameElem.innerText;
    const teamName = prompt("Team name", existingName);
    nameElem.innerText = teamName;
}

function addpoints(card) {
    const parent = card.parentNode;
    const pointsElem = parent.querySelector(".score-points");
    let existingPoints = Number(pointsElem.innerText);
    existingPoints += 200;
    pointsElem.innerText = existingPoints;
}

function rempoints(card) {
    const parent = card.parentNode;
    const pointsElem = parent.querySelector(".score-points");
    let existingPoints = Number(pointsElem.innerText);
    existingPoints -= 200;
    if (existingPoints >= 0) {
        pointsElem.innerText = existingPoints;
    }
}