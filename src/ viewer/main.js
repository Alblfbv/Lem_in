/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.js                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfleury <jfleury@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/10 10:30:45 by jfleury           #+#    #+#             */
/*   Updated: 2019/04/10 17:41:46 by jfleury          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
* Install "npm i readline-sync"
*/


const readlineSync = require('readline-sync');

function		ft_parser()
{
	var		final_string = '';
	var 	string;

	while (string = readlineSync.question(''))
		final_string += string;
	return final_string;
}

function		ft_print(final_string)
{
	console.log(final_string);
}

async function		main()
{
	var		string;

	console.log("TEST 1");
	string = ft_parser();
	ft_print(string);
	console.log("TEST 2");
}
main();
