getData = function() {
	var debut = 2000;
	var fin = 2018;
	var moisCoule = [2,3,4]
	
	var annees = [];
	
	for(var i = debut; i<=fin; ++i) {
		annees.push(i);
	}
	
	for(i in annees) {
		for(j in moisCoule) {
			console.log(annees[i] + ' : ' + moisCoule[j] + ' | ' +calcURL(annees[i],moisCoule[j]));
			open(calcURL(annees[i],moisCoule[j]), '_blank');
		}
	}
	
}

calcURL = function(annee, mois) {
	return 	"http://climat.meteo.gc.ca/climate_data/bulk_data_f.html?format=csv&stationID=5502&Year=" + annee + "&Month=" + mois + "&Day=14&timeframe=1&submit=++T%C3%A9l%C3%A9charger+%0D%0Ades+donn%C3%A9es";
}